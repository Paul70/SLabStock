#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "libslabstock/database/connector.h"
#include "tests/libslabstock/database/mocks/mariadbconnectormocks.h"
#include "tests/testbase.h"

using namespace SLABSTOCK::Database;

namespace {
class DBConnectorTests : public TestBase
{};
}  // namespace

TEST_F(DBConnectorTests, testDBConnectorConstructor)
{
  // benötige construction data
  // dann kann ich das object machen
  // und dann muss ich meine mocks testen
  // DBConnector
}

TEST_F(DBConnectorTests, testSomethingForException)
{
  //W_EXPECT_THROW("do something exceptional", "something bad is going on");
}
