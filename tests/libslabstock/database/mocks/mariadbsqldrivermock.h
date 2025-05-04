#ifndef SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTORMOCKS_H
#define SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTORMOCKS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mariadb/conncpp.hpp>
#include <memory>
#include <string>

namespace SLABSTOCK::Tests::Database::Mocks {

// Mock class for sql::Driver
class MockSqlDriver : public sql::Driver
{
  public:
  MOCK_METHOD(sql::Connection*, connect, (const sql::SQLString&, const sql::Properties&),
              (const, override));
  MOCK_METHOD(sql::Connection*, connect,
              (const sql::SQLString&, const sql::SQLString&, const sql::SQLString&),
              (const, override));
  MOCK_METHOD(sql::Connection*, connect, (const sql::Properties&), (const, override));
  MOCK_METHOD(bool, acceptsURL, (const sql::SQLString&), (const, override));
  MOCK_METHOD(uint32_t, getMajorVersion, (), (const, override));
  MOCK_METHOD(uint32_t, getMinorVersion, (), (const, override));
  MOCK_METHOD(bool, jdbcCompliant, (), (const, override));
  MOCK_METHOD(const sql::SQLString&, getName, (), (const, override));
};

}  // namespace SLABSTOCK::Tests::Database::Mocks
#endif  // SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTORMOCKS
