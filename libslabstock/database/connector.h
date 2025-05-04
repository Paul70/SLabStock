#ifndef SLABSTOCK_CONNECTOR_H
#define SLABSTOCK_CONNECTOR_H
#include "types.h"

#include "libd/libdutil/loggingsource.h"

#include <memory>
#include <string>

namespace sql {
class Connection;
class Statement;
}  // namespace sql

namespace SLABSTOCK::Database {
class SqlDriverFactory;
class ResultSet;

/*! \brief Mariadb database connector class.
 *
 * Longer description of Connector.
 */

class Connector : public DUTIL::LoggingSource
{
  public:
  //! Construct with construction data
  explicit Connector(std::string_view database_url, std::string_view database_user,
                     SqlDriverFactory const& sqlDriverFactory,
                     DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  ~Connector();

  sql::Connection const& getConnection() const;

  Types::SqlStmtResultPair getTableResultSetAndStatmentHandle(
      std::string const& sqlStatement) const;

  Types::SqlTableMetaData getTableMetaData(Types::SqlResultSetReader resultSet) const;

  private:
  void connect();
  void close();

  Types::SqlStatementHandle getSqlStatementHandler() const;

  static constexpr char const* password_{"123test"};
  const std::string database_url_;
  const std::string database_user_;

  SqlDriverFactory const& sqlDriverFactory_;
  std::unique_ptr<sql::Connection> connection_;
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_CONNECTOR_H
