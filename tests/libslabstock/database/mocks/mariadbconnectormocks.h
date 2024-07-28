#ifndef SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTORMOCKS_H
#define SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTORMOCKS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mariadb/conncpp/Properties.hpp>
#include <memory>
#include <string>

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK::Tests::Database::Mocks {

/*! \brief Create interfaces for the MariaDB connector classes you want to mock:
 *
 * - IResultSet
 * - IStatement
 * - IConnection
 * - IDriver
 */

class IResultSet
{
  public:
  virtual ~IResultSet() = default;
  virtual bool next() = 0;
  virtual int getInt(const std::string& column) = 0;
  virtual std::string getString(const std::string& column) = 0;
};

class IStatement
{
  public:
  virtual ~IStatement() = default;
  virtual std::unique_ptr<IResultSet> executeQuery(const std::string& query) = 0;
};

class IConnection
{
  public:
  virtual ~IConnection() = default;
  virtual std::unique_ptr<IStatement> createStatement() = 0;
};

class IDriver
{
  public:
  virtual ~IDriver() = default;
  virtual std::unique_ptr<IConnection> connect(const std::string& url,
                                               const sql::Properties& properties)
      = 0;
};

/*! \brief Create mock classes that implement these interfaces:
 *
 * - MockDriver -> IDriver
 * - MockResultSet -> IResultSet
 * - MockStatement -> IStatement
 * - MockConnection -> IConnection
 */

class MockDriver : public IDriver
{
  public:
  MOCK_METHOD(std::unique_ptr<IConnection>, connect,
              (const std::string& url, const sql::Properties& properties), (override));
};

class MockConnection : public IConnection
{
  public:
  MOCK_METHOD(std::unique_ptr<IStatement>, createStatement, (), (override));
};

class MockStatement : public IStatement
{
  public:
  MOCK_METHOD(std::unique_ptr<IResultSet>, executeQuery, (const std::string& query), (override));
};

class MockResultSet : public IResultSet
{
  public:
  MOCK_METHOD(bool, next, (), (override));
  MOCK_METHOD(int, getInt, (const std::string& column), (override));
  MOCK_METHOD(std::string, getString, (const std::string& column), (override));
};

}  // namespace SLABSTOCK::Tests::Database::Mocks
#endif  // SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTORMOCKS
