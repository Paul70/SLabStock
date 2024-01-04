#include "simulationbase.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_FACTORYINTERFACE(::SLABSTOCK::SimulationBase)

const ConstructionValidator SimulationBase::getConstructionValidator()
{
  static const ConstructionValidator cv;
  return cv;
}

SimulationBase::SimulationBase(DUTIL::ConstructionData const&,
                               LoggingSource::LoggingSinkPointer sink) :
    LoggingSource(sink),
    eventMap_(),
    eventQueue_(),
    now_(0)
{
  this->trace("Default construction of '" + ProjectWare::getShortConcreteClassName() + "'.");
}
