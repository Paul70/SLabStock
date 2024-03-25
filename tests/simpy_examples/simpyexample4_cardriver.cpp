#include "tests/testbase.h"

#include "libslabstock/simulation/interrupt.h"
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
class SimPyExampleElectricCarDriverTests4 : public TestBase
{};

class ExampleDriver4 : public Process, public D_NAMED_CLASS(::ExampleDriver4)
{
  public:
  D_DECLARE_PROCESS(ExampleDriver4);

  static constexpr char const* chargingStartedKey = "chargingStarted";
  static constexpr label_t interruptAfter = 3;
  D_NAMED_PARAMETER(ProcessToInterrupt, Event::Id);

  using Process::Process;

  private:
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTargetEvent) override
  {
    auto currentValue = getValue();
    Event::Id processToInterrupt = currentValue.s.getParameter<ProcessToInterrupt>();
    if (!currentValue.s.value(chargingStartedKey).isMonostate()) {
      info("Driver is interrupting charging at " + Utility::toString(sim.now()));
      Interrupt::newInstance(sim, ConstructionData().setParameter<Description>("impatient driver"),
                             sim.getEvent<Process>(processToInterrupt));
      return true;
    }
    currentValue.s.set(chargingStartedKey, true);
    info("Driver starting to wait at " + Utility::toString(sim.now()));
    newTargetEvent = Timeout::newInstance(sim, "delay until driver loses patience", interruptAfter);
    setValue(currentValue);
    return false;
  }

  // clang-format off
  virtual std::string whatAmIImpl() const override
  {
    return getClassName();
  }

  virtual bool finalizeImpl(SimulationBase&) override
  {
    return true;
  }

  // clang-format on
};

class ExampleCharger4 : public Process, public D_NAMED_CLASS(::ExampleCharger4)
{
  public:
  D_DECLARE_PROCESS(ExampleCharger4);
  static constexpr char const* chargingStartedKey = "chargingStarted";
  static constexpr label_t chargeDuration = 5;

  using Process::Process;

  private:
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTargetEvent) override
  {
    auto currentValue = getValue();
    if (!currentValue.s.value(chargingStartedKey).isMonostate())
      return true;
    currentValue.s.set(chargingStartedKey, true);
    newTargetEvent = Timeout::newInstance(sim, "delay until charging ends", chargeDuration);
    setValue(currentValue);
    return false;
  }

  // clang-format off
  virtual std::string whatAmIImpl() const override
  {
    return getClassName();
  }

  virtual bool finalizeImpl(SimulationBase&) override
  {
    return true;
  }

  // clang-format on
};

class ExampleCar4 : public Process, public D_NAMED_CLASS(::ExampleCar4)
{
  public:
  D_DECLARE_PROCESS(ExampleCar4);
  D_NAMED_ENUM(DrivingState, PARKING, DRIVING);
  static constexpr label_t tripDuration = 2;

  using Process::Process;

  Event::Id parking(SimulationBase& sim)
  {
    info("Start parking and charging at " + Utility::toString(sim.now()));
    return Process::initWithParent(
        sim,
        ConstructionData{}.setConcreteClassParameter<ExampleCharger4>().setParameter<Description>(
            "Example 3 charger"));
  }

  Event::Id driving(SimulationBase& sim)
  {
    info("Start driving at " + Utility::toString(sim.now()));
    return Timeout::newInstance(sim, "delay until driving ends", tripDuration);
  }

  private:
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTargetId) override
  {
    auto currentValue = getValue();
    if (currentValue.s.getEnum<DrivingState>() == DrivingState::DRIVING) {
      currentValue.setEnum(DrivingState::PARKING);
      newTargetId = parking(sim);
    } else {
      currentValue.setEnum(DrivingState::DRIVING);
      newTargetId = driving(sim);
    }
    setValue(currentValue);
    return false;
  }

  virtual bool interruptImpl(SimulationBase& sim, Interrupt& i, Event::Id& newTargetEvent) override
  {
    info("Was interrupted by " + i.getDescription() + " at " + Utility::toString(sim.now())
         + ". Hope the battery is full enough...");
    setValue(getValue().setEnum(DrivingState::DRIVING));
    newTargetEvent = driving(sim);
    return false;
  }

  // clang-format off
  virtual std::string whatAmIImpl() const override
  {
    return getClassName();
  }

  virtual bool finalizeImpl(SimulationBase&) override
  {
    return true;
  }

  // clang-format on
};

//! Static factory memeber definitions
D_DEFINE_PROCESS(ExampleDriver4);
D_DEFINE_PROCESS(ExampleCharger4);
D_DEFINE_PROCESS(ExampleCar4);
}  // namespace

TEST_F(SimPyExampleElectricCarDriverTests4, exampleCardriver4_worksAsExpected)
{
  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);
  Simulation sim(sls);
  auto car = Process::initWithParent(sim, ConstructionData{}
                                              .setConcreteClassParameter<ExampleCar4>()
                                              .setParameter<Event::Description>("Example 3 car")
                                              .setEnum(ExampleCar4::DrivingState::DRIVING));
  Process::init(sim, ConstructionData{}
                         .setConcreteClassParameter<ExampleDriver4>()
                         .setParameter<ExampleDriver4::ProcessToInterrupt>(car)
                         .setParameter<Event::Description>("Example 3 driver"));

  sim.runUntil(15);
  EXPECT_EQ(sim.now(), 15);

  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking and charging at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Driver starting to wait at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Driver is interrupting charging at 3"));
  EXPECT_THAT(os,
              testing::HasSubstr(
                  "Was interrupted by impatient driver at 3. Hope the battery is full enough.."));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 3"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking and charging at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 10"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking and charging at 12"));
}
