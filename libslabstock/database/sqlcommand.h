#ifndef SLABSTOCK_DATABASE_SQLCOMMAND_H
#define SLABSTOCK_DATABASE_SQLCOMMAND_H

#include <string>

namespace SLABSTOCK::Database {

/*! \brief description of SqlCommand
 *
 * Longer description of SqlCommand.
 */

class SqlCommand
{
  public:
  /**
    * @brief Return Sql command to show all tables of a database.
    *
    * @param [in] None
    * @return Sql command string.
    */
  static std::string sqlShowTables();

  /**
   * @brief Return Sql command to remove a table from a database.
   *
   * @param [in] name of the table
   * @return Sql command string.
   */
  static std::string sqlRemoveTable(std::string_view table_name);

  /**
   * @brief Return Sql command to check if a table exists in
   *        a database.
   *
   * @param [in] name of the database
   * @param [in] name of the table
   * @return Sql command string.
   */
  static std::string sqlSelectExistTableInDatabase(std::string_view database_name,
                                                   std::string_view table_name);

  /**
   * @brief Return Sql command to get all data in a database table.
   *
   * @param [in] name of the table
   * @return Sql command string.
   */
  static std::string sqlSelectAll(std::string_view table_name);

  /**
   * @brief Return Sql command to get the number of rows and columns from a database table.
   *
   * The sql command returns the following result table:
   *
   * | row_count | col_count |
   * -------------------------
   * |     X     |      Y    |
   * ------------------------
   *
   * @param [in] name of the table
   * @return Sql command string.
   */
  static constexpr char const* ROW_COUNT_COLUMN{"row_count"};
  static constexpr char const* COL_COUNT_COLUMN{"col_count"};
  static constexpr int ROW_COUNT_INDEX{0};
  static constexpr int COL_COUNT_INDEX{0};
  static constexpr int NUMBER_ROWS{1};
  static constexpr int NUMBER_COLS{2};
  static std::string sqlGetTableSize(std::string_view table_name);
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_DATABASE_SQLCOMMAND_H
