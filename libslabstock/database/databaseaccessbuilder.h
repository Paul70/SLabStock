#ifndef SLABSTOCK_DATABASE_DATABASEACCESSBUILDER_H
#define SLABSTOCK_DATABASE_DATABASEACCESSBUILDER_H
#include "sqldatabaseaccess.h"

#include <string>

namespace SLABSTOCK::Database {

/*! \brief description of SqlTableDescription
 *
 * Longer description of SqlTableDescription.
 */
class DatabaseAccessBuilder
{
  public:
  template <typename DatabaseAccessType = SqlDatabaseAccess>
  static DatabaseAccessType createDatabaseAccess(std::string const& database,
                                                 std::string const& user)
  {
    auto cd = DatabaseAccessType::buildConstructionData(database, user);
    return DatabaseAccessType(cd);
  }
};
}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_DATABASE_DATABASEACCESSBUILDER_H
