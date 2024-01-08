#include "callback.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_FACTORYINTERFACE(::SLABSTOCK::Callback)

DUTIL::ConstructionValidator const& Callback::getConstructinValidator()
{
  static ConstructionValidator cv;
  return cv;
}
