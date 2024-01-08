#include "initialize.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_EVENT(Initialize)

ConstructionValidator const& Initialize::getConstructionValidator()
{
  using WR = WarelistRule;
  // clant-format off
  static const ConstructionValidator cv(
      {}, {WR::forSubobject<Initialize::ProcessToStart>("Define Process settings")},
      Event::getConstructionValidator());
  // clant-format on
  return cv;
}

Initialize::Initialize(ConstructionData const& cd, LoggingSinkPointer sink) :
    Event(cd, sink)
{}

std::string Initialize::whatAmIImpl() const
{
  return Initialize::getClassName();
}
