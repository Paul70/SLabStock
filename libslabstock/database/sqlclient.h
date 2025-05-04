#ifndef SLABSTOCK_DATABASE_DBSERVICE_H
#define SLABSTOCK_DATABASE_DBSERVICE_H
#include "sqldriverfactory.h"
#include "types.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/loggingsource.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/projectware.h"

#include <memory>
#include <string>

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK::Database {
class Connector;
class SqlDriverFactory;

/*! \brief description of DBService
 *
 * Longer description of DBService.
 */

class SqlClient :
    public DUTIL::ProjectWare,
    public DUTIL::LoggingSource,
    public D_NAMED_CLASS(::SLABSTOCK::Database::DBService)
{
  public:
  //! Static factory memeber.
  D_DECLARE_PROJECTWARE(SqlClient)

  //! Set the database url.
  D_NAMED_STRING(SqlDatabaseName)

  //! Set the database user.
  D_NAMED_STRING(SqlDatabaseUser)

  //! Define set of rules to validate construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data
  explicit SqlClient(DUTIL::ConstructionData const& cd,
                     DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  ~SqlClient();

  Types::SqlStmtResultPair getSqlResultStatementPair(std::string const& sqlStatement) const;

  Types::SqlTableMetaData getSqlTableMetaData(Types::SqlResultSetReader resultSet) const;

  private:
  std::string sqlDatabase_;
  std::string sqlUser_;

  MariaDBDriverFactory sqlDriverFactory_;
  std::unique_ptr<Connector> connector_;
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_DATABASE_DBSERVICE_H
