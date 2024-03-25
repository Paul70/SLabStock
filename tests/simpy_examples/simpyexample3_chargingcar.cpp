#include "tests/testbase.h"

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
class SimPyExampleElectricCarTests3 : public TestBase
{};

class ExampleCharger final : public Process, public D_NAMED_CLASS(::ExampleCharger)
{
  public:
  //! Static factory memeber declaration
  D_DECLARE_PROCESS(ExampleCharger)

  static constexpr char const* chargingStartedKey = "chargingStarted";
  static constexpr label_t chargeDuration = 5;

  //! Inherit Process constructor and ConstructionValidator.
  using Process::getConstructionValidator;
  using Process::Process;

  private:
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTarget) override
  {
    auto currentValue = getValue();
    if (!currentValue.s.value(chargingStartedKey).isMonostate())
      return true;
    currentValue.s.set(chargingStartedKey, true);
    setValue(currentValue);
    newTarget = Timeout::newInstance(sim, "delay until charging ends", chargeDuration);
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

class ExampleElectricCar final : public Process, public D_NAMED_CLASS(::ExampleElectricCar)
{
  public:
  //! Static factory memeber declaration
  D_DECLARE_PROCESS(ExampleElectricCar)

  //! Possible set of car conditions.
  D_NAMED_ENUM(DrivingState, DRIVING, PARKING)

  static constexpr label_t tripDuration = 2;

  //! Inherit Process constructor and ConstructionValidator.
  using Process::getConstructionValidator;
  using Process::Process;

  /*! \brief Implementation of parking.
   *
   *  Parking means, that the ExampleElecltricCar process has nothing to do
   *  but the ExampleCharger porcess starts now working. Therefore, we have to
   *  create a ExampleCharger process and put it into the simulation
   *
   * \param:
   * sim: Referece to the simulation instance.
   */
  Event::Id parking(SimulationBase& sim)
  {
    info("Start parking and charging at " + Utility::toString(sim.now()));
    return Process::initWithParent(
        sim,
        ConstructionData{}.setConcreteClassParameter<ExampleCharger>().setParameter<Description>(
            "Example charger"));
  }

  Event::Id driving(SimulationBase& sim)
  {
    info("Start driving at " + Utility::toString(sim.now()));
    return Timeout::newInstance(sim, "delay until driving ends", tripDuration);
  }

  private:
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTarget) override
  {
    auto currentValue = getValue();
    if (currentValue.s.getEnum<ExampleElectricCar::DrivingState>()
        == ExampleElectricCar::DrivingState::PARKING) {
      currentValue.setEnum(ExampleElectricCar::DrivingState::DRIVING);
      newTarget = driving(sim);
    } else {
      currentValue.setEnum(ExampleElectricCar::DrivingState::PARKING);
      newTarget = parking(sim);
    }
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

//! Static factory memeber definitions
D_DEFINE_PROCESS(ExampleElectricCar)
D_DEFINE_PROCESS(ExampleCharger)
}  // namespace

TEST_F(SimPyExampleElectricCarTests3, electricCar3_worksAsExpected)
{
  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);

  Simulation sim(sls);

  Process::init(sim, ConstructionData{}
                         .setConcreteClassParameter<ExampleElectricCar>()
                         .setEnum(ExampleElectricCar::DrivingState::DRIVING)
                         .setParameter<Event::Description>("Example 2 car"));
  sim.runUntil(15);
  EXPECT_EQ(sim.now(), 15);

  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking and charging at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking and charging at 7"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 12"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking and charging at 14"));
}
