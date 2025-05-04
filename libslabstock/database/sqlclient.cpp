#include "sqlclient.h"
#include "connector.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK::Database;

D_DEFINE_PROJECTWARE(SqlClient)

ConstructionValidator const& SqlClient::getConstructionValidator()
{
  using SR = SettingRule;
  static ConstructionValidator cv(

      {SR::forNamedParameter<SqlClient::SqlDatabaseName>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                         "Mandatory sql database url address."),
       SR::forNamedParameter<SqlClient::SqlDatabaseUser>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                         "Mandatory sql database user name.")});
  return cv;
}

SqlClient::SqlClient(ConstructionData const& cd, DUTIL::LoggingSource::LoggingSinkPointer sink) :
    LoggingSource(sink),
    sqlDatabase_(getConstructionValidator().validateNamedParameter<SqlClient::SqlDatabaseName>(cd)),
    sqlUser_(getConstructionValidator().validateNamedParameter<SqlClient::SqlDatabaseUser>(cd)),
    connector_(std::make_unique<Connector>(sqlDatabase_, sqlUser_, sqlDriverFactory_, sink))
{}

SqlClient::~SqlClient() {}

Types::SqlStmtResultPair SqlClient::getSqlResultStatementPair(std::string const& sqlStatement) const
{
  auto pair = connector_->getTableResultSetAndStatmentHandle(sqlStatement);
  return pair;
}

Types::SqlTableMetaData SqlClient::getSqlTableMetaData(Types::SqlResultSetReader resultSet) const
{
  return connector_->getTableMetaData(resultSet);
}

//bool DBService::doesTableExist(std::string_view table_name)
//{
//  advanceState(Signal::NEW_QUERY,
//               "DBService:\nNew database query: 'doesTableExist()': " + std::string(table_name));

//  SqlTable result;
//  auto statement = SqlCommand::sqlSelectExistTableInDatabase(database_, table_name);
//  auto status = connector_->executeSqlStatementSynchron(statement, result);

//  if (!checkSqlState(status, std::move(statement))) {
//    return false;
//  }

//  auto value = result.getValue("COUNT(*)", 0);
//  if (std::get<std::string>(value.value()) == "1") {
//    return true;
//  }
//  return false;
//}

//std::pair<std::int8_t, std::int8_t> DBService::getTableSize(std::string_view table_name)
//{
//  advanceState(Signal::NEW_QUERY,
//               "DBService:\nNew database query: 'getTableSize()': " + std::string(table_name));
//  SqlTable result;

//  auto statement = SqlCommand::sqlGetTableSize(table_name);
//  auto status = connector_->executeSqlStatementBlockingMode(statement, result);

//  if (!checkSqlState(status, std::move(statement))) {
//    return {};
//  }

//  auto no_rows = result.getValue(SqlCommand::ROW_COUNT, SqlCommand::ROW_COUNT_INDEX);
//  auto no_cols = result.getValue(SqlCommand::COL_COUNT, SqlCommand::COL_COUNT_INDEX);
//  try {
//    return {
//        DUTIL::Utility::stringToArithmetic<std::int8_t>(std::get<std::string>(no_rows.value())),
//        DUTIL::Utility::stringToArithmetic<std::int8_t>(std::get<std::string>(no_cols.value()))};
//  } catch (std::bad_optional_access const& e) {
//    D_ASSERT(false);
//  }
//}

//void DBService::getIsinMappingTable(SqlTable& sql_result)
//{
//  std::string table_name = "isin_mapping";

//  auto dim = getTableSize(table_name);
//  sql_result.resize(dim.first, dim.second);

//  advanceState(Signal::NEW_QUERY, "DBService:\nNew database query: 'getIsinMappingTable()'.");

//  std::string statement = SqlCommand::sqlSelectAll(table_name);
//  auto status = connector_->executeSqlStatementSynchron(statement, sql_result);
//  if (!checkSqlState(status, std::move(statement))) {
//    return;
//  }

//  if (sql_result.isEmpty()) {
//    advanceState(Signal::REPLY_ERROR,
//                 "SqlClient:\nSql reply error: Could not fetch results from database.");
//  } else {
//    advanceState(Signal::REPLY_OK, "SqlClient:\nSql reply ok.");
//  }
//}

//SqlClient::ReplyState SqlClient::setTableSize(ResultSet& /*table*/) const
//{
// ResultSet table_size("size");  // sql statement ist eig mit dem table name klar
// table_size.description_.sqlStatement_ = SqlCommand::sqlGetTableSize(table.description_.name_);
// table_size.description_.rows_ = SqlCommand::NUMBER_ROWS;
// table_size.description_.cols_ = SqlCommand::NUMBER_COLS;

// auto status = connector_->executeSqlStatementBlockingMode(table_size);
// if (status == DBConnector::SqlState::ERROR)
// {
//   error("DBService: Sql satement failed: " + table.description_.sqlStatement_.value());
//   return ReplyState::SQL_ERROR;
// }

// auto rows = table_size.getValue(SqlCommand::ROW_COUNT_COLUMN, SqlCommand::ROW_COUNT_INDEX);
// auto cols = table_size.getValue(SqlCommand::COL_COUNT_COLUMN, SqlCommand::COL_COUNT_INDEX);

// table.description_.rows_.emplace(
//     Utility::stringToArithmetic<std::size_t>(std::get<std::string>(rows.value())));
// table.description_.cols_.emplace(
//     Utility::stringToArithmetic<std::size_t>(std::get<std::string>(cols.value())));

//  table.description_.rows_
//      = table_size
//            .getValueAs<std::int>(SqlCommand::ROW_COUNT_COLUMN, SqlCommand::ROW_COUNT_INDEX)
//            .value();
//  table.description_.cols_
//      = table_size
//            .getValueAs<std::size_t>(SqlCommand::COL_COUNT_COLUMN, SqlCommand::COL_COUNT_INDEX)
//            .value();

//}

// SqlClient::ReplyState SqlClient::getDbTable(ResultSet& table) const
// {
//   if (!table.description_.rows_.has_value() && !table.description_.cols_.has_value())
//   {
//     auto state = setTableSize(table);
//     if (state == ReplyState::SQL_ERROR)
//     {
//       return state;
//     }
//   }

//   table.description_.sqlStatement_ = SqlCommand::sqlSelectAll(table.description_.name_);

//   //auto status = connector_->executeSqlStatementBlockingMode(table);
//   // if (status == DBConnector::SqlState::ERROR)
//   // {
//   //   error("DBService: Sql satement failed: " + table.description_.sqlStatement_.value());
//   //   return ReplyState::SQL_ERROR;
//   // }

//   return ReplyState::REPLY_OK;
// }
