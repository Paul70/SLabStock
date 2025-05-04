#ifndef SLABSTOCK_DATABASE_TESTS_MARIADBSQLSTATEMENTMOCKS_H
#define SLABSTOCK_DATABASE_TESTS_MARIADBSQLSTATEMENTMOCKS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mariadb/conncpp.hpp>
#include <memory>
#include <string>

namespace SLABSTOCK::Tests::Database::Mocks {

// Mock class for sql::Statement
class MockStatement : public sql::Statement
{
  public:
    MOCK_METHOD(bool, execute, (const sql::SQLString&), (override));
    MOCK_METHOD(bool, execute, (const sql::SQLString&, int32_t), (override));
    MOCK_METHOD(bool, execute, (const sql::SQLString&, int32_t*), (override));
    MOCK_METHOD(bool, execute, (const sql::SQLString&, const sql::SQLString*), (override));

    MOCK_METHOD(sql::ResultSet*, executeQuery, (const sql::SQLString&), (override));

    MOCK_METHOD(int32_t, executeUpdate, (const sql::SQLString&), (override));
    MOCK_METHOD(int32_t, executeUpdate, (const sql::SQLString&, int32_t), (override));
    MOCK_METHOD(int32_t, executeUpdate, (const sql::SQLString&, int32_t*), (override));
    MOCK_METHOD(int32_t, executeUpdate, (const sql::SQLString&, const sql::SQLString*), (override));

    MOCK_METHOD(int64_t, executeLargeUpdate, (const sql::SQLString&), (override));
    MOCK_METHOD(int64_t, executeLargeUpdate, (const sql::SQLString&, int32_t), (override));
    MOCK_METHOD(int64_t, executeLargeUpdate, (const sql::SQLString&, int32_t*), (override));
    MOCK_METHOD(int64_t, executeLargeUpdate, (const sql::SQLString&, const sql::SQLString*), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(uint32_t, getMaxFieldSize, (), (override));
    MOCK_METHOD(void, setMaxFieldSize, (uint32_t), (override));
    MOCK_METHOD(int32_t, getMaxRows, (), (override));
    MOCK_METHOD(void, setMaxRows, (int32_t), (override));
    MOCK_METHOD(int64_t, getLargeMaxRows, (), (override));
    MOCK_METHOD(void, setLargeMaxRows, (int64_t), (override));
    MOCK_METHOD(void, setEscapeProcessing, (bool), (override));
    MOCK_METHOD(int32_t, getQueryTimeout, (), (override));
    MOCK_METHOD(void, setQueryTimeout, (int32_t), (override));
    MOCK_METHOD(void, cancel, (), (override));
    MOCK_METHOD(sql::SQLWarning*, getWarnings, (), (override));

    MOCK_METHOD(void, clearWarnings, (), (override));
    MOCK_METHOD(void, setCursorName, (const sql::SQLString&), (override));
    MOCK_METHOD(sql::Connection*, getConnection, (), (override));
    MOCK_METHOD(sql::ResultSet*, getGeneratedKeys, (), (override));
    MOCK_METHOD(int32_t, getResultSetHoldability, (), (override));
    MOCK_METHOD(bool, isClosed, (), (override));
    MOCK_METHOD(bool, isPoolable, (), (override));
    MOCK_METHOD(void, setPoolable, (bool), (override));
    MOCK_METHOD(sql::ResultSet*, getResultSet, (), (override));
    MOCK_METHOD(int32_t, getUpdateCount, (), (override));
    MOCK_METHOD(int64_t, getLargeUpdateCount, (), (override));
    MOCK_METHOD(bool, getMoreResults, (), (override));
    MOCK_METHOD(bool, getMoreResults, (int32_t), (override));
    MOCK_METHOD(int32_t, getFetchDirection, (), (override));
    MOCK_METHOD(void, setFetchDirection, (int32_t), (override));
    MOCK_METHOD(int32_t, getFetchSize, (), (override));
    MOCK_METHOD(void, setFetchSize, (int32_t), (override));
    MOCK_METHOD(int32_t, getResultSetConcurrency, (), (override));
    MOCK_METHOD(int32_t, getResultSetType, (), (override));
    MOCK_METHOD(void, addBatch, (const sql::SQLString&), (override));
    MOCK_METHOD(void, clearBatch , (), (override));
    MOCK_METHOD(const sql::Ints&, executeBatch, (), (override));
    MOCK_METHOD(const sql::Longs&, executeLargeBatch , (), (override));
    MOCK_METHOD(void, closeOnCompletion, (), (override));
    MOCK_METHOD(bool, isCloseOnCompletion, (), (override));
    MOCK_METHOD(Statement*, setResultSetType, (int32_t), (override));
};


}  // namespace SLABSTOCK::Tests::Database::Mocks
#endif // SLABSTOCK_DATABASE_TESTS_MARIADBSQLSTATEMENTMOCKS_H
