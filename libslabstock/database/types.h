#ifndef SLABSTOCK_SQLTYPES_H
#define SLABSTOCK_SQLTYPES_H
#include <memory>

namespace DUTIL {
struct ConstructionData;
}

namespace sql {
class ResultSet;
class ResultSetMetaData;
class Statement;
}  // namespace sql

namespace SLABSTOCK::Database {
class SqlClient;
}

namespace SLABSTOCK::Database::Types {

/*! \brief description of SqlTypes
 *
 * Longer description of SqlTypes.
 */
using DbClient = std::unique_ptr<SLABSTOCK::Database::SqlClient>;
using SqlResultSet = std::unique_ptr<sql::ResultSet>;
using SqlResultSetReader = sql::ResultSet const&;
using SqlStatementHandle = std::unique_ptr<sql::Statement>;
using SqlStmtResultPair = std::pair<SqlResultSet, SqlStatementHandle>;

using SqlTableMetaData = std::unique_ptr<sql::ResultSetMetaData>;

}  // namespace SLABSTOCK::Database::Types
#endif  // SLABSTOCK_SQLTYPES_H
