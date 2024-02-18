#include "libslabstock/simulation/simulation.h"
#include "tests/testbase.h"

using namespace SLABSTOCK;
using namespace DUTIL;

namespace {
class SimulationTests : public TestBase
{};
}  // namespace

TEST_F(SimulationTests, testConstructEmptySimulation)
{
  //Simulation sim;
  //EXPECT_TRUE(sim.isEmpty());
  //EXPECT_TRUE(sim.getStartTime_ms() == 0);
  //EXPECT_TRUE(sim.getUnusedEventId() == 0);
}

TEST_F(SimulationTests, testSomethingForException)
{
  //W_EXPECT_THROW("do something exceptional", "something bad is going on");
}
