#ifndef SLABSTOCK_DATABASE_SQLDATABASE_H
#define SLABSTOCK_DATABASE_SQLDATABASE_H
#include "idatabaseaccess.h"
#include "isinmapping.h"
#include "types.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/projectware.h"

namespace sql {
class ResultSetMetaData;
class ResultSet;
}  // namespace sql

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK::Database {
class SqlClient;
class SqlTable;

/*! \brief description of SqlResult
 *
 * Longer description of SqlResult.
 * - wrapper um ein sql result set
 */

class SqlDatabase final :
    public IValueAccess<SqlDatabase>,
    public DUTIL::ProjectWare,
    public D_NAMED_CLASS(::SLABSTOCK::Database::SqlDatabase)
{
  public:
  //! Static factory memeber.
  D_DECLARE_PROJECTWARE(SqlDatabase)

  //! Object instance offering access to the sql database table
  D_NAMED_REFERENCE(DatabaseTableClient, SqlClient)

  //! Set the name of the SQL table to get access to
  D_NAMED_STRING(SqlTableName)

  //! Set Sql Statement for filtering the sql result set
  D_NAMED_STRING(SqlStatement)

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data
  explicit SqlDatabase(DUTIL::ConstructionData const& cd);

  ~SqlDatabase() override;

  template <typename T>
  void setCallback(std::function<void(T)> callback) const
  {
    isin_->exportData<T>(callback);
  }

  private:
  void setDataExportCallbackImpl() const override;
  void executeQueryImpl(const std::string& query) const override;
  void queryTableImpl() const override;

  Types::DbClient sqlClient_;
  std::string sqlTable_;
  std::shared_ptr<IsinMapping> isin_;
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_DATABASE_SQLDATABASE_H
