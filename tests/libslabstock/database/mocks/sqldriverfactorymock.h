#ifndef SLABSTOCK_DATABASE_TESTS_SQLDRIVERFACTORYMOCK_H
#define SLABSTOCK_DATABASE_TESTS_SQLDRIVERFACTORYMOCK_H

#include "libslabstock/database/sqldriverfactory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace SLABSTOCK::Tests::Database::Mocks {

class MockMariaDBDriverFactory : public SLABSTOCK::Database::SqlDriverFactory {
public:
    MOCK_METHOD(sql::Driver*, createDriver, (), (const, override));
};
}

#endif // SLABSTOCK_DATABASE_TESTS_SQLDRIVERFACTORYMOCK_H
