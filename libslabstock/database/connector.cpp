#include "connector.h"
#include "sqldriverfactory.h"

#include <mariadb/conncpp.hpp>

using namespace DUTIL;
using namespace SLABSTOCK::Database;

Connector::Connector(std::string_view database_url, std::string_view database_user,
                     SqlDriverFactory const& sqlDriverFactory,
                     DUTIL::LoggingSource::LoggingSinkPointer sink) :
    LoggingSource(sink),
    database_url_(database_url),
    database_user_(database_user),
    sqlDriverFactory_(sqlDriverFactory),
    connection_(nullptr)
{
  connect();
}

Connector::~Connector()
{
  close();
}

void Connector::connect()
{
  D_ASSERT(!connection_);

  try
  {
    // Initialize the driver
    sql::Driver* driver = sqlDriverFactory_.createDriver();

    // Connection properties
    sql::SQLString url(database_url_);
    sql::Properties properties({{"user", database_user_}, {"password", password_}});

    // database connection
    connection_.reset(driver->connect(url, properties));
  }
  catch (sql::SQLException const& e)
  {
    error("DBConnector: Connection to database '" + database_url_ + "' failed: " + e.what());
  }
  catch (std::exception const& e)
  {
    error("DBConnector: Connection to database '" + database_url_ + "' failed: " + e.what());
  }
  catch (...)
  {
    error("DBConnector: Connection to database '" + database_url_ + "' failed: Unknown error.");
  }

  D_ASSERT(connection_);
  trace("DBConnector: Established connection to database '" + database_url_ + "'.");
}

void Connector::close()
{
  if (!connection_)
  {
    return;
  }

  try
  {
    connection_->close();
  }
  catch (sql::SQLException const& e)
  {
    connection_.reset(nullptr);
    error("DBConnector: Closing connection to database' " + database_url_
          + "' failed: " + e.what());
  }

  trace("DBConnector: Closed connection to database' " + database_url_ + "'.");
}

sql::Connection const& Connector::getConnection() const
{
  D_ASSERT(connection_);
  return *connection_;
}

Types::SqlStmtResultPair Connector::getTableResultSetAndStatmentHandle(
    std::string const& sqlStatement) const
{
  D_ASSERT(connection_);

  auto stmtHandler = getSqlStatementHandler();
  D_ASSERT(stmtHandler);

  Types::SqlResultSet resultSet = nullptr;

  try
  {
    // execute statement
    resultSet.reset(stmtHandler->executeQuery(sqlStatement));

    // get metadata
    std::unique_ptr<sql::ResultSetMetaData> metadata(nullptr);
    metadata.reset(resultSet->getMetaData());
  }
  catch (sql::SQLException const& e)
  {
    error("DBConnector: Query of sql statement failed, no result set available: "
          + std::string(e.what()));
    return {};
  }
  catch (std::exception const& e)
  {
    error("DBConnector: Query of sql statement failed, no result set available: "
          + std::string(e.what()));
    return {};
  }

  D_ASSERT(resultSet);
  D_ASSERT(stmtHandler);
  return {std::move(resultSet), std::move(stmtHandler)};
}

Types::SqlTableMetaData Connector::getTableMetaData(Types::SqlResultSetReader resultSet) const
{
  std::unique_ptr<sql::ResultSetMetaData> metadata(nullptr);
  metadata.reset(resultSet.getMetaData());
  D_ASSERT(metadata);
  return metadata;
}

Types::SqlStatementHandle Connector::getSqlStatementHandler() const
{
  try
  {
    std::unique_ptr<sql::Statement> stmtHandler = nullptr;
    stmtHandler.reset(connection_->createStatement());
    return stmtHandler;
  }
  catch (sql::SQLException const& e)
  {
    error("DBConnector: Creation of sql statement handler failed: " + std::string(e.what()));
    return {};
  }
  catch (std::exception const& e)
  {
    error("DBConnector: Creation of sql statement handler failed: " + std::string(e.what()));
    return {};
  }
}
