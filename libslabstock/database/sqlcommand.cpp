#include "sqlcommand.h"

using namespace SLABSTOCK::Database;

std::string SqlCommand::sqlShowTables()
{
  return "SHOW TABLES;";
}

std::string SqlCommand::sqlRemoveTable(std::string_view table_name)
{
  return "DROP TABLE " + std::string(table_name) + ";";
}

std::string SqlCommand::sqlSelectExistTableInDatabase(std::string_view database_name,
                                                      std::string_view table_name)
{
  return "SELECT COUNT(*) FROM information_schema.TABLES WHERE TABLE_SCHEMA = '"
         + std::string(database_name) + "' AND TABLE_NAME = '" + std::string(table_name) + "';";
}

std::string SqlCommand::sqlSelectAll(std::string_view table_name)
{
  return "SELECT * FROM " + std::string(table_name) + ";";
}

std::string SqlCommand::sqlGetTableSize(std::string_view table_name)
{
  return "SELECT (SELECT COUNT(*) FROM " + std::string(table_name) + ") AS " + ROW_COUNT_COLUMN + ", (SELECT COUNT(*) FROM "
         "INFORMATION_SCHEMA.COLUMNS WHERE table_name = '" + std::string(table_name) + "') AS " + COL_COUNT_COLUMN + ";";
}
