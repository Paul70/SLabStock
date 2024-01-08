#ifndef SLABSTOCK_TESTS_TESTBASE_H
#define SLABSTOCK_TESTS_TESTBASE_H
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

class TestBase : public ::testing::Test
{};  // TestBase

#endif  // SLABSTOCK_TESTS_TESTBASE_H
