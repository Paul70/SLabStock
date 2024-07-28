#ifndef SLABSTOCK_CONNECTOR_H
#define SLABSTOCK_CONNECTOR_H

#include <memory>
#include <string>
#include "libd/libdutil/loggingsource.h"
#include "libd/libdutil/namedparameter.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace sql {
class Connection;
class Statement;
}  // namespace sql

namespace SLABSTOCK::Database {

/*! \brief Mariadb database connector class.
 *
 * Longer description of Connector.
 */

class DBConnector : public DUTIL::LoggingSource
{
  public:
  //! Database url address as string parameter
  D_NAMED_STRING(Database_Url)

  //! Database user name
  D_NAMED_STRING(Database_User)

  //! Define set of rules to validate construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data
  explicit DBConnector(DUTIL::ConstructionData const& cd,
                       DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  ~DBConnector();

  private:
  void connect();
  void close();

  static constexpr char const* password_{"123test"};
  std::string database_url_;
  std::string database_user_;

  std::unique_ptr<sql::Connection> connection_;
  std::unique_ptr<sql::Statement> statement_;
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_CONNECTOR_H
