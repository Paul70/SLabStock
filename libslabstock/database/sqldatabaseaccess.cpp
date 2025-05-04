#include "sqldatabaseaccess.h"
#include "sqlclient.h"
#include "sqldatabase.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK::Database;

D_DEFINE_PROJECTWARE(SqlDatabaseAccess)

ConstructionValidator const& SqlDatabaseAccess::getConstructionValidator()
{
  using WR = WarelistRule;
  static const DUTIL::ConstructionValidator cv(
      {/*no setting rules yet*/},
      {WR::forSubobject<SqlDatabaseAccess::SqlDatabaseBridge>(
          "Sql database client offering access to the database table content.")});

  return cv;
}

ConstructionData SqlDatabaseAccess::buildConstructionData(std::string const& database,
                                                          std::string const& user)
{
  using CD = DUTIL::ConstructionData;
  return CD().addSubobject<SqlDatabaseBridge>(
      // Construction data object for SqlFacade and its derived classes
      CD().setConcreteClassParameter<SqlDatabase>()
          .addSubobject<SqlDatabase::DatabaseTableClient>(
              CD().setConcreteClassParameter<SqlClient>()
                  .setParameter<SqlClient::SqlDatabaseName>(database)
                  .setParameter<SqlClient::SqlDatabaseUser>(user))
          .setParameter<SqlDatabase::SqlTableName>("isin_mapping"));
}

SqlDatabaseAccess::SqlDatabaseAccess(DUTIL::ConstructionData const& cd) :
    db_(getConstructionValidator().buildSubobject<SqlDatabaseAccess::SqlDatabaseBridge>(cd))
{}

SqlDatabaseAccess::~SqlDatabaseAccess() {}

void SqlDatabaseAccess::runQuery(const std::string& query) const
{
  db_->executeQuery(query);
}

void SqlDatabaseAccess::queryTable()
{
  db_->queryTable();
}

template <typename T>
void SqlDatabaseAccess::exportValueCallback(std::function<void(T)> callback) const
{
  db_->setDataExportCallback<T>(callback);
}

//! Explicit instantiations, otherwise we have to implement the
//! template function body in the header file.
// clang-format off
template void SqlDatabaseAccess::exportValueCallback<std::int8_t>(
    std::function<void(std::int8_t)>) const;
template void SqlDatabaseAccess::exportValueCallback<std::int16_t>(
    std::function<void(std::int16_t)>) const;
template void SqlDatabaseAccess::exportValueCallback<std::int32_t>(
    std::function<void(std::int32_t)>) const;
template void SqlDatabaseAccess::exportValueCallback<std::int64_t>(
    std::function<void(std::int64_t)>) const;
template void SqlDatabaseAccess::exportValueCallback<double>(
    std::function<void(double)>) const;
template void SqlDatabaseAccess::exportValueCallback<std::string>(
    std::function<void(std::string)>) const;
// clang-format on
