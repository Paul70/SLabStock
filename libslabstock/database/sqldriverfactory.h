#ifndef SLABSTOCK_SQLDIRVERFACTORY_H
#define SLABSTOCK_SQLDIRVERFACTORY_H

#include <mariadb/conncpp.hpp>

namespace SLABSTOCK::Database {

/*! \brief description of SqlDirverFactory
 *
 * Longer description of SqlDirverFactory.
 */

class SqlDriverFactory
{
  public:
  virtual ~SqlDriverFactory() = default;
  virtual sql::Driver* createDriver() const = 0;
};

class MariaDBDriverFactory : public SqlDriverFactory
{
  public:
  sql::Driver* createDriver() const override { return sql::mariadb::get_driver_instance(); }
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_SQLDIRVERFACTORY_H
