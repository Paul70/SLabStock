#include "libslabstock/database/sqlcommand.h"
#include "tests/testbase.h"

using namespace SLABSTOCK::Database;

namespace {
class SqlCommadTests : public TestBase
{};
}  // namespace

TEST_F(SqlCommadTests, sqlCommand_showTables)
{
  ASSERT_EQ(SqlCommand::sqlShowTables(), "SHOW TABLES;");
}

TEST_F(SqlCommadTests, sqlCommand_removeTable)
{
  std::string table_name{"test_table_name"};
  std::string command{"DROP TABLE test_table_name;"};
  ASSERT_EQ(SqlCommand::sqlRemoveTable(table_name), command);
}

TEST_F(SqlCommadTests, sqlCommand_sqlSelectExistTableInDatabase)
{
  std::string database_name{"test_database_name"};
  std::string table_name{"test_table_name"};
  std::string command{
      "SELECT COUNT(*) FROM information_schema.TABLES WHERE TABLE_SCHEMA = 'test_database_name' "
      "AND TABLE_NAME = 'test_table_name';"};
  ASSERT_EQ(SqlCommand::sqlSelectExistTableInDatabase(database_name, table_name), command);
}

TEST_F(SqlCommadTests, sqlCommand_sqlSelectAll)
{
  std::string table_name{"test_table_name"};
  std::string command{"SELECT * FROM test_table_name;"};
  ASSERT_EQ(SqlCommand::sqlRemoveTable(table_name), command);
}
