#include "isinmapping.h"
#include "sqlclient.h"
#include "sqlcommand.h"

#include <cassert>
#include <mariadb/conncpp.hpp>

using namespace DUTIL;
using namespace SLABSTOCK::Database;

IsinMapping::IsinMapping(SqlClient const& sqlClient) :
    sqlStatement_(),
    sqlClient_(sqlClient),
    sqlStmtResult_()
{}

void IsinMapping::setStatementImpl(const std::string& statement)
{
  assert(!statement.empty());
  sqlStatement_ = statement;
}

void IsinMapping::queryStatementImpl(const std::string& statement)
{
  if (!statement.empty())
  {
    sqlStatement_ = statement;
  }
  assert(!sqlStatement_.empty());

  sqlStmtResult_ = (sqlClient_.getSqlResultStatementPair(sqlStatement_));
  assert(sqlStmtResult_.first);
  assert(sqlStmtResult_.second);
}

void IsinMapping::queryTableContentImpl()
{
  sqlStatement_ = SqlCommand::sqlSelectAll(ISIN_TABLE);
  sqlStmtResult_ = (sqlClient_.getSqlResultStatementPair(sqlStatement_));
  assert(sqlStmtResult_.first);
  assert(sqlStmtResult_.second);
}

void IsinMapping::exportIntData(std::function<void(int)> callback) const
{
  assert(resultSet_);
  auto in = 7;
  callback(in);
}

void IsinMapping::exportStringData(std::function<void(std::string)> callback) const
{
  assert(!sqlStatement_.empty());

  while (sqlStmtResult_.first->next())
  {
    auto value = sqlStmtResult_.first->getString(COL_SYMBOL);
    callback(std::string(value.c_str()));
  }
}

bool IsinMapping::hasNext() const
{
  return resultSet_->next();
}
