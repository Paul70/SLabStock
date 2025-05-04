#include "sqltable.h"

using namespace SLABSTOCK::Database;

void SqlTable::setStatement(const std::string& statement)
{
  setStatementImpl(statement);
}

void SqlTable::queryStatement(const std::string& statement)
{
  queryStatementImpl(statement);
}

void SqlTable::queryTableContent()
{
  queryTableContentImpl();
}
