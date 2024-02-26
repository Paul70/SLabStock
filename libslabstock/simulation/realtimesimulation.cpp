#include "realtimesimulation.h"

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
    clock_(*getConstructionValidator().buildSubobject<RealTimeSimulation::RealTime>(cd)),
    tolerance_s_(
        getConstructionValidator().validateNamedParameter<RealTimeSimulation::Tolerance_s>(cd))
{
  this->trace("Finished construction of '" + this->getShortConcreteClassName()
              + "' without ConstructionData.");
}

RealTimeSimulation::RealTimeSimulation(DUTIL::LoggingSource::LoggingSinkPointer sink) :
    SimulationBase(ConstructionData(), sink)
{
  this->trace("Finished construction of '" + this->getShortConcreteClassName()
              + "' without ConstructionData.");
}

void RealTimeSimulation::runUntilLastEventImpl()
{

  D_ASSERT(!(now() > 0));

  // activate the clock and set the absolute start time value in milli seconds
  clock_.initialize();

  this->info("Startig real time simulation");
}
