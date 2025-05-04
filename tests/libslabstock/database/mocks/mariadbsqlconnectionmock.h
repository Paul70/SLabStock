#ifndef SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTIONMOCKS_H
#define SLABSTOCK_DATABASE_TESTS_MARIADBCONNECTIONMOCKS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mariadb/conncpp.hpp>
#include <memory>
#include <string>

namespace SLABSTOCK::Tests::Database::Mocks {

class MockSqlConnection : public sql::Connection
{
  public:
  MOCK_METHOD(sql::Statement*, createStatement, (), (override));
  MOCK_METHOD(sql::Statement*, createStatement, (int32_t, int32_t), (override));
  MOCK_METHOD(sql::Statement*, createStatement, (int32_t, int32_t, int32_t), (override));

  MOCK_METHOD(sql::PreparedStatement*, prepareStatement, (const sql::SQLString&), (override));
  MOCK_METHOD(sql::PreparedStatement*, prepareStatement, (const sql::SQLString&, int32_t, int32_t),
              (override));
  MOCK_METHOD(sql::PreparedStatement*, prepareStatement,
              (const sql::SQLString&, int32_t, int32_t, int32_t), (override));
  MOCK_METHOD(sql::PreparedStatement*, prepareStatement, (const sql::SQLString&, int32_t),
              (override));
  MOCK_METHOD(sql::PreparedStatement*, prepareStatement, (const sql::SQLString& sql, int32_t*),
              (override));
  MOCK_METHOD(sql::PreparedStatement*, prepareStatement,
              (const sql::SQLString& sql, const sql::SQLString*), (override));

  MOCK_METHOD(sql::CallableStatement*, prepareCall, (const sql::SQLString&), (override));
  MOCK_METHOD(sql::CallableStatement*, prepareCall, (const sql::SQLString&, int32_t, int32_t),
              (override));
  MOCK_METHOD(sql::CallableStatement*, prepareCall,
              (const sql::SQLString&, int32_t, int32_t, int32_t), (override));

  MOCK_METHOD(sql::SQLString, nativeSQL, (const sql::SQLString&), (override));

  MOCK_METHOD(bool, getAutoCommit, (), (override));
  MOCK_METHOD(void, setAutoCommit, (bool), (override));

  MOCK_METHOD(void, commit, (), (override));

  MOCK_METHOD(void, rollback, (), (override));
  MOCK_METHOD(void, rollback, (const sql::Savepoint*), (override));

  MOCK_METHOD(void, close, (), (override));
  MOCK_METHOD(bool, isClosed, (), (override));

  MOCK_METHOD(sql::DatabaseMetaData*, getMetaData, (), (override));
  MOCK_METHOD(bool, isReadOnly, (), (override));
  MOCK_METHOD(void, setReadOnly, (bool), (override));
  MOCK_METHOD(sql::SQLString, getCatalog, (), (override));
  MOCK_METHOD(void, setCatalog, (const sql::SQLString&), (override));
  MOCK_METHOD(int32_t, getTransactionIsolation, (), (override));
  MOCK_METHOD(void, setTransactionIsolation, (int32_t), (override));
  MOCK_METHOD(sql::SQLWarning*, getWarnings, (), (override));
  MOCK_METHOD(void, clearWarnings, (), (override));
  MOCK_METHOD(int32_t, getHoldability, (), (override));
  MOCK_METHOD(void, setHoldability, (int32_t), (override));
  MOCK_METHOD(sql::Savepoint*, setSavepoint, (), (override));
  MOCK_METHOD(sql::Savepoint*, setSavepoint, (const sql::SQLString&), (override));
  MOCK_METHOD(void, releaseSavepoint, (const sql::Savepoint*), (override));

  MOCK_METHOD(bool, isValid, (int32_t), (override));
  MOCK_METHOD(bool, isValid, (), (override));

  MOCK_METHOD(sql::SQLString, getUsername, (), (override));
  MOCK_METHOD(sql::SQLString, getHostname, (), (override));

  MOCK_METHOD(sql::SQLString, getSchema, (), (override));
  MOCK_METHOD(void, setSchema, (const sql::SQLString&), (override));

  MOCK_METHOD(void, setClientInfo, (const sql::SQLString&, const sql::SQLString&), (override));
  MOCK_METHOD(void, setClientInfo, (const sql::Properties&), (override));
  MOCK_METHOD(sql::Properties, getClientInfo, (), (override));
  MOCK_METHOD(sql::SQLString, getClientInfo, (const sql::SQLString&), (override));

  MOCK_METHOD(int32_t, getNetworkTimeout, (), (override));
  MOCK_METHOD(void, reset, (), (override));
  MOCK_METHOD(bool, reconnect, (), (override));

  MOCK_METHOD(sql::Connection*, setClientOption, (const sql::SQLString&, void*), (override));
  MOCK_METHOD(sql::Connection*, setClientOption, (const sql::SQLString&, const sql::SQLString&),
              (override));
  MOCK_METHOD(void, getClientOption, (const sql::SQLString&, void*), (override));
  MOCK_METHOD(sql::SQLString, getClientOption, (const sql::SQLString&), (override));

  MOCK_METHOD(sql::Clob*, createClob, (), (override));
  MOCK_METHOD(sql::Blob*, createBlob, (), (override));
  MOCK_METHOD(sql::NClob*, createNClob, (), (override));
  MOCK_METHOD(sql::SQLXML*, createSQLXML, (), (override));
};

}  // namespace SLABSTOCK::Tests::Database::Mocks
#endif  // MARIADBSQLCONNECTIONMOCK_H
