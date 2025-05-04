#include "idatabaseaccess.h"

using namespace DUTIL;
using namespace SLABSTOCK::Database;

void IDatabaseAccess::setDataExportCallback() const
{
  setDataExportCallbackImpl();
}

void IDatabaseAccess::executeQuery(const std::string& query) const
{
  executeQueryImpl(query);
}

// ConstructionValidator const& IDatabaseAccess::getConstructionValidator()
// {
//   static ConstructionValidator cv;
//   return cv;
// }

void IDatabaseAccess::queryTable() const
{
  queryTableImpl();
}

//IDatabaseAccess::IDatabaseAccess(ConstructionData const&) {}
