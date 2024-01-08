#include "tests/testbase.h"

#include "libslabstock/simulation/process.h"
#include "libslabstock/simulation/simulation.h"
#include "libslabstock/simulation/timeout.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

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

  //! Inherit Process constructor.
  using Process::Process;

  Event::Id parking(SimulationBase& sim) { return Timeout::newInstance(sim, "", parkingDuration); }

  Event::Id driving(SimulationBase& sim) { return Timeout::newInstance(sim, "", tripDuration); }

  private:
  virtual std::string whatAmIImpl() const override { return getClassName(); }

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
    return false;
  }
};

D_DEFINE_PROCESS(ExampleCar)

}  // namespace

TEST_F(SimPyExampleCarTests, testWhatAmI)
{
  //ExampleCar car;
  //EXPECT_EQ(car.whatAmI(), ExampleCar::getClassName());
}

TEST_F(SimPyExampleCarTests, testExampleCarManualSimulation)
{
  Simulation sim;
  // clang-format off
  Process::init(sim, ConstructionData().setConcreteClassParameter<ExampleCar>()
                                       .setEnum(ExampleCar::DrivingState::PARKING)
                                       .setParameter<Event::Description>("Example 1 car"));
  // clang-format on
}
