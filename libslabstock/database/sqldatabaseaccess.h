#ifndef SLABSTOCK_DATABASE_SQLDATABASEACCESS_H
#define SLABSTOCK_DATABASE_SQLDATABASEACCESS_H

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/namedreference.h"
#include "libd/libdutil/projectware.h"

#include <string>

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK::Database {
class SqlDatabase;

/*! \brief description of Table
 *
 * Longer description of Table.
 */

class SqlDatabaseAccess :
    public DUTIL::ProjectWare,
    public D_NAMED_CLASS(::SLABSTOCK::Database::SqlDatabaseAccess)
{
  public:
  //! Static factory memeber.
  D_DECLARE_PROJECTWARE(SqlDatabaseAccess)

  //! Shared pointer offering access to the sql database table
  // das soll variabel sein
  D_NAMED_REFERENCE(SqlDatabaseBridge, SqlDatabase)

  //! Return the validator for construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  static DUTIL::ConstructionData buildConstructionData(std::string const& database,
                                                       std::string const& user);

  //! Construct with construction data
  explicit SqlDatabaseAccess(DUTIL::ConstructionData const& cd);

  ~SqlDatabaseAccess() override;

  void runQuery(const std::string& query) const;

  void queryTable();

  template <typename T>
  void exportValueCallback(std::function<void(T)> callback) const;

  protected:
  SqlDatabase* myPtr;
  std::unique_ptr<SqlDatabase> db_;
};

}  // namespace SLABSTOCK::Database

#endif  // SLABSTOCK_DATABASE_SQLDATABASEACCESS_H
