#include "realtimesimulation.h"
#include <unistd.h>
#include "finalize.h"

#include "libd/libdutil/clock.h"

#include <algorithm>

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_SIMULATIONBASE(RealTimeSimulation)

ConstructionValidator const& RealTimeSimulation::getConstructionValidator()
{
  using SR = SettingRule;
  using WR = WarelistRule;
  static const ConstructionValidator cv(
      {[]() {
        SR sr = SR::forNamedParameter<RealTimeSimulation::Tolerance_s>(
            SR::Usage::MANDATORY_WITH_DEFAULT,
            "Define how much the real-time-simulation is allowed to lag behind wall clock time.\n"
            "When the next event is scheduled the simulation will normally sleep until the "
            "desired\n"
            "wall clock time is reached. If that time has already passed, then we have a lag and "
            "the next event\n"
            "is processed immediately. If the lag exceeds the given tolerance the simulation is\n"
            "aborted and the simulation load should be redistributed to additional simulations.");
        sr.defaultValue = 1.0;  // value in seconds
        return sr;
      }()},

      // Warelist rules
      {WR::forSubobject<RealTimeSimulation::RealTime>("Define the clock object to measure time.")});
  return cv;
}

RealTimeSimulation::RealTimeSimulation(ConstructionData const& cd,
                                       DUTIL::LoggingSource::LoggingSinkPointer sink) :
    SimulationBase(cd, sink),
    clock_(),
    tolerance_s_(
        getConstructionValidator().validateNamedParameter<RealTimeSimulation::Tolerance_s>(cd))
{
  auto clock = getConstructionValidator().buildSubobject<RealTimeSimulation::RealTime>(cd);
  if (clock) {
    clock_ = std::move(clock);
  } else {
    clock_ = std::make_unique<DUTIL::Clock>();
  }

  this->trace("Finished construction of '" + this->getShortConcreteClassName()
              + "' without ConstructionData.");
}

RealTimeSimulation::RealTimeSimulation(DUTIL::LoggingSource::LoggingSinkPointer sink) :
    SimulationBase(ConstructionData(), sink)
{
  this->trace("Finished construction of '" + this->getShortConcreteClassName()
              + "' without ConstructionData.");
}

RealTimeSimulation::~RealTimeSimulation() {}

void RealTimeSimulation::runUntilLastEventImpl()
{
  D_ASSERT(!(now() > 0));

  // activate the clock and set the absolute start time value in milli seconds
  clock_->initialize();

  // start simulation
  this->info("Startig real time simulation");
  update(SimulationSignaler::SimulationState::RUNNING);

  // set timer delay.
  stepAndDelayImpl(false);
}

void RealTimeSimulation::startSimulationImpl()
{
  this->info("Start signalled");
  runUntilLastEventImpl();
}

void RealTimeSimulation::stopSimulationImpl()
{
  this->info("Stop signalled");
  Finalize::newInstance(*this, 0);
}

void RealTimeSimulation::stepAndDelayImpl(bool doStep)
{
  if (doStep) {
    step();
  }

  if (isEmpty()) {
    this->info("No more events to process, ending simulation");
    update(SimulationSignaler::SimulationState::STOPPED);
    finishSimulation();
    return;
  }

  // calculate lag till next scheduled event time.
  clock_->advance();
  auto elapsed_nano_sec = clock_->elapsed(TIME::UnitPrefix::NANO);
  auto nextEventTime = peekNextTime(TIME::UnitPrefix::NANO);
  auto lag_ms = static_cast<int>((elapsed_nano_sec - nextEventTime) * TIME::nanoByMilli);
  auto lag_s = lag_ms / TIME::oneByMilli;

  // If tolerance is violated, throw.
  if (lag_s >= tolerance_s_) {
    D_THROW("Simulation was too slow, simulation lag " + Utility::toString(lag_s)
            + " s is higher than tolerance of " + Utility::toString(tolerance_s_) + " s.");
  }

  // Set timer
  setTimer(std::max(0, -lag_ms));
}
