#include "initialize.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_EVENT(Initialize)

ConstructionValidator const& Initialize::getConstructionValidator()
{
  using WR = WarelistRule;
  // clang-format off
  static const ConstructionValidator cv(
      {},
      {WR::forSubobject<Initialize::ProcessToStart>("Define Process settings")},
      Event::getConstructionValidator());
  // clang-format on
  return cv;
}

ConstructionData Initialize::getProcessCD(Event const& event)
{
  // in cd brauch ich hier noch ne fucntion mit der ich das subovje
  return event.getValue().getSubObjectCd<ProcessToStart>();
}

Initialize::Initialize(ConstructionData const& cd, LoggingSinkPointer sink) :
    Event(cd, sink)
{
  this->trace("Construction of Initialize event. \nTarget porcess: "
              + ProcessToStart::getReferenceName());
}

std::string Initialize::whatAmIImpl() const
{
  return Initialize::getClassName();
}
