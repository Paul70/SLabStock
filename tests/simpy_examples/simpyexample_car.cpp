#include "libslabstock/simulation/processinitializecallback.h"
#include "tests/testbase.h"

#include "libslabstock/simulation/initialize.h"
#include "libslabstock/simulation/process.h"
#include "libslabstock/simulation/simulation.h"
#include "libslabstock/simulation/timeout.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/streamloggingsink.h"

#include <chrono>
#include <sstream>

using namespace SLABSTOCK;
using namespace DUTIL;

namespace {
class SimPyExampleCarTests : public TestBase
{};

class ExampleCar final : public Process, public D_NAMED_CLASS(::ExampleCar)
{
  public:
  D_DECLARE_PROCESS(ExampleCar)

  D_NAMED_ENUM(DrivingState, DRIVING, PARKING)

  static constexpr label_t parkingDuration = 5;
  static constexpr label_t tripDuration = 2;

  //! Inherit Process constructor and ConstructionValidator.
  using Process::getConstructionValidator;
  using Process::Process;

  Event::Id parking(SimulationBase& sim)
  {
    this->info("Start parking at " + Utility::toString(sim.now()));
    return Timeout::newInstance(
        sim, "Car is starts now parking for " + Utility::toString(parkingDuration) + "time units",
        parkingDuration);
  }

  Event::Id driving(SimulationBase& sim)
  {
    this->info("Start driving at " + Utility::toString(sim.now()));
    return Timeout::newInstance(
        sim, "Car is starts now driving for " + Utility::toString(tripDuration) + "time units",
        tripDuration);
  }

  private:
  // clang-format off
  virtual std::string whatAmIImpl() const override
  {
    return getClassName();
  }

  // clang-format on

  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTargetEvent) override
  {
    auto currentValue = getValue();
    if (currentValue.s.getEnum<ExampleCar::DrivingState>() == ExampleCar::DrivingState::PARKING) {
      currentValue.setEnum(ExampleCar::DrivingState::DRIVING);
      newTargetEvent = driving(sim);
    } else {
      currentValue.setEnum(ExampleCar::DrivingState::PARKING);
      newTargetEvent = parking(sim);
    }
    setValue(currentValue);
    return false;
  }

  virtual bool finalizeImpl(SimulationBase&) override { return true; }
};

D_DEFINE_PROCESS(ExampleCar)

}  // namespace

TEST_F(SimPyExampleCarTests, testWhatAmI)
{
  ExampleCar car(Process::getDefaultConstructionData());
  EXPECT_EQ(car.whatAmI(), ExampleCar::getClassName());
}

TEST_F(SimPyExampleCarTests, testExampleCarManualSimulationSetup)
{
  // log stream pionter
  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);

  // Alternative: just creat a logger which itself constructs its stream object.
  Simulation sim(sls);

  // clang-format off
  Process::init(sim, ConstructionData().setConcreteClassParameter<ExampleCar>()
                                       .setEnum(ExampleCar::DrivingState::DRIVING)
                                       .setParameter<Event::Description>("Example 1 car"));
  // clang-format on

  // test if simulation and proecess 'Example 1 car' were constructed correctly.
  // simulation has to consits of:
  // - event map: 1 Initialize event targeting process ExampleCar (ProcessToStart member)
  //              Process ExampleCar gets created via PorcessInitializeCallback as soon as the
  //              Initialize event gets processed.
  //
  // - event queue: Constains one scheduled Initialize event at the moment.The concrete process
  //                ExampleCar gets scheduled as soo as it es created via method SimulationBase::create().
  auto id = sim.getNextEvent();
  auto& event = sim.getEvent<SLABSTOCK::Initialize>(id);
  auto name = event.whatAmI();
  ASSERT_EQ(name, "::SLABSTOCK::Initialize");
  auto processCD = event.getProcessCD(event);
  ASSERT_EQ(processCD.s.getParameter<Event::Description>().value(), "Example 1 car");

  // start simulation and run until given time tick is reached.
  // Afterwards, simulation event queue has to be empty.
  sim.runUntil(15);
  EXPECT_TRUE(sim.isEmpty());
  EXPECT_EQ(sim.now(), 15);

  // check log messages
  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 7"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 12"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 14"));
}

TEST_F(SimPyExampleCarTests, testExampleCarManualSimulationSetupDoneWithConstructionData)
{
  using CD = ConstructionData;
  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);

  Simulation sim(CD().set(Dataset(std::vector<DUTIL::Now::Tick>{0, 0, 0}, 3))
                     .addSubobject<Simulation::EventList>(
                         CD().setParameter<Initialize::IdParam>(0)
                             .setParameter<Initialize::Description>("init for Example 1 car")
                             .addSubobject<Initialize::CallbackList>(
                                 CD().setConcreteClassParameter<ProcessInitializeCallback>())
                             .addSubobject<Initialize::ProcessToStart>(
                                 CD().setParameter<Event::IdParam>(1)
                                     .setParameter<Process::TargetId>(0)
                                     .setEnum(ExampleCar::DrivingState::DRIVING)
                                     .setParameter<Event::Description>("Example 1 car")
                                     .setConcreteClassParameter<ExampleCar>())
                             .setConcreteClassParameter<Initialize>()),
                 sls);

  sim.runUntil(15);
  EXPECT_EQ(sim.now(), 15);

  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 7"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 12"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 14"));
}
