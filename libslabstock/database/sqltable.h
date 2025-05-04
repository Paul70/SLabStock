#ifndef SLABSTOCK_DATABASE_SQLTABLE_H
#define SLABSTOCK_DATABASE_SQLTABLE_H
#include <string>

namespace SLABSTOCK::Database {

/*! \brief description of SqlTableDescription
 *
 * Longer description of SqlTableDescription.
 */
class SqlTable
{
  public:
  SqlTable() = default;

  virtual ~SqlTable() = default;

  void setStatement(const std::string& statement);

  void queryStatement(const std::string& statement);

  void queryTableContent();

  private:
  virtual void setStatementImpl(const std::string& statement) = 0;
  virtual void queryStatementImpl(const std::string& statement) = 0;
  virtual void queryTableContentImpl() = 0;
};
}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_DATABASE_SQLTABLE_H
