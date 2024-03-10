#include "callback.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_FACTORYINTERFACE(::SLABSTOCK::Callback)

DUTIL::ConstructionValidator const& Callback::getConstructionValidator()
{
  // dummy validator, has no rules.
  static ConstructionValidator cv;
  return cv;
}

void Callback::operator()(SimulationBase& sim, Event& event) const
{
  callbackImpl(sim, event);
}
