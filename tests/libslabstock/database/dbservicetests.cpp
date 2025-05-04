#include "libslabstock/database/dbservice.h"
#include "libslabstock/database/sqlresult.h"
#include "tests/testbase.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace DUTIL;
using namespace SLABSTOCK::Database;

namespace {
class DBServiceTests : public TestBase
{};
}  // namespace

TEST_F(DBServiceTests, test_DBService_doesTableExist)
{
  const std::string tableName{"depots"};

  DBService dbService(
      ConstructionData()
          .setParameter<DBService::Database>("jdbc:mariadb://localhost:3306/slabstock_test")
          .setParameter<DBService::DatabaseUser>("test_user"));

  SqlResult result;
  dbService.getIsinMappingTable(result);
}

TEST_F(DBServiceTests, testSomethingForException)
{
  //W_EXPECT_THROW("do something exceptional", "something bad is going on");
}
