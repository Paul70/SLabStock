#include "sqldatabase.h"
#include "isinmapping.h"
#include "sqlclient.h"
#include "sqlcommand.h"

#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK::Database;

D_DEFINE_PROJECTWARE(SqlDatabase)

ConstructionValidator const& SqlDatabase::getConstructionValidator()
{
  using SR = SettingRule;
  using WR = WarelistRule;
  static const ConstructionValidator cv(
      {SR::forNamedParameter<SqlDatabase::SqlTableName>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                        "Define the sql table to be accessed"),
       SR::forNamedParameter<SqlDatabase::SqlStatement>(
           SR::Usage::OPTIONAL, "Define an optionanl sql default statement")},
      {WR::forSubobject<SqlDatabase::DatabaseTableClient>(
          "Sql database client offering access to the database table content.")});

  return cv;
}

SqlDatabase::SqlDatabase(ConstructionData const& cd) :
    sqlClient_(getConstructionValidator().buildSubobject<SqlDatabase::DatabaseTableClient>(cd)),
    sqlTable_(getConstructionValidator().validateNamedParameter<SqlDatabase::SqlTableName>(cd)),
    isin_(std::make_shared<IsinMapping>(*sqlClient_))
//isin_(std::dynamic_pointer_cast<SqlTable>(std::make_shared<IsinMapping>(*sqlClient_)))

{
  auto sqlStatement
      = getConstructionValidator().validateNamedParameter<SqlDatabase::SqlStatement>(cd);
  if (sqlStatement.value().empty())
  {
    isin_->setStatement(SqlCommand::sqlSelectAll(sqlTable_));
  }
}

SqlDatabase::~SqlDatabase() {}

void SqlDatabase::setDataExportCallbackImpl() const {}

void SqlDatabase::executeQueryImpl(const std::string& query) const
{
  isin_->queryStatement(query);
}

void SqlDatabase::queryTableImpl() const
{
  isin_->queryTableContent();
}
