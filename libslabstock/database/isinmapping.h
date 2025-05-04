#ifndef SLABSTOCK_ISINMAPPING_H
#define SLABSTOCK_ISINMAPPING_H
#include "sqltable.h"
#include "types.h"

#include <cstdint>
#include <functional>
#include <type_traits>

namespace sql {
class ResultSet;
}

namespace SLABSTOCK::Database {
class SqlClient;

class IsinMapping final : public SqlTable
{
  public:
  //! Construct with construction data
  explicit IsinMapping(SqlClient const& sqlClient);

  virtual ~IsinMapping() override = default;

  template <typename T>
  void exportData(std::function<void(T)> callback) const
  {
    if constexpr (std::is_same_v<T, std::string>)
    {
      exportStringData(callback);
    }
    else
    {
      exportIntData(callback);
    }
  }

  private:
  // clang-format off
  static constexpr char const* ISIN_TABLE {"isin_mapping"};
  static constexpr char const* COL_ISIN   {"ISIN"};
  static constexpr char const* COL_NAME   {"name"}; // in Name
  static constexpr char const* COL_SYMBOL {"TA_key"}; // in Symbol
  static constexpr char const* COL_HOLD   {"hold"}; //
  // clang-format on

  virtual void setStatementImpl(const std::string& statement) override;
  virtual void queryStatementImpl(const std::string& statement) override;
  virtual void queryTableContentImpl() override;

  void exportIntData(std::function<void(int)>) const;
  void exportStringData(std::function<void(std::string)>) const;

  bool hasNext() const;

  std::string sqlStatement_;
  SqlClient const& sqlClient_;
  Types::SqlStmtResultPair sqlStmtResult_;
  Types::SqlResultSet resultSet_;
  Types::SqlStatementHandle sqlStmtHandle_;
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_ISINMAPPING_H
