#include "connector.h"
#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

#include <iostream>
#include <mariadb/conncpp.hpp>

using namespace DUTIL;
using namespace SLABSTOCK::Database;

ConstructionValidator const& DBConnector::getConstructionValidator()
{
  using SR = SettingRule;
  static ConstructionValidator cv(
      {[]() {
         SR sr = SR::forNamedParameter<DBConnector::Database_Url>(
             SR::Usage::MANDATORY_NO_DEFAULT, "Url address of database as string.");
         return sr;
       }(),
       []() {
         SR sr = SR::forNamedParameter<DBConnector::Database_User>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                                   "Database user name string.");
         return sr;
       }()});
  return cv;
}

DBConnector::DBConnector([[maybe_unused]] ConstructionData const& cd,
                         DUTIL::LoggingSource::LoggingSinkPointer sink) :
    LoggingSource(sink),
    database_url_(
        DBConnector::getConstructionValidator().validateNamedParameter<DBConnector::Database_Url>(
            cd)),
    database_user_(
        DBConnector::getConstructionValidator().validateNamedParameter<DBConnector::Database_User>(
            cd)),
    connection_(nullptr),
    statement_(nullptr)
{
  connect();
}

DBConnector::~DBConnector()
{
  close();
}

void DBConnector::connect()
{
  D_ASSERT_MSG("Database connection parameter already set.", !connection_);
  D_ASSERT_MSG("Database statement parameter already set.", !statement_);

  try {
    // Initialize the driver
    sql::Driver* driver = sql::mariadb::get_driver_instance();

    // Connection properties
    sql::SQLString url(database_url_);
    sql::Properties properties({{"user", database_user_}, {"password", password_}});

    // Create a connection, statement and result set - reset because connect method delivers raw pointer.
    connection_.reset(driver->connect(url, properties));
    statement_.reset(connection_->createStatement());

    // Execute a query
    //    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM table_name"));

    //    // Process the results
    //    while (res->next()) {
    //      std::cout << "id = " << res->getInt("id") << std::endl;
    //      std::cout << "name = " << res->getString("name") << std::endl;
    //    }

  } catch (sql::SQLException& e) {
    debug("DBConnector: Connection to database '" + database_url_ + "' failed");
    std::cerr << "SQLException: " << e.what() << std::endl;
    std::cerr << "SQLState: " << e.getSQLState() << std::endl;
  }

  debug("DBConnector: Established connection to database '" + database_url_ + "'");
}

void DBConnector::close()
{
  if (connection_ != nullptr) {
    connection_->close();
    if (connection_->isClosed()) {
      debug("Closed connection to '" + database_url_ + "'.");
    } else {
      error("Could not close connection to '" + database_url_ + "'.");
    }
  }
}
