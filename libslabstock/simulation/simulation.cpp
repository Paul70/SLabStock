#include "simulation.h"

#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_SIMULATION(Simulation)

DUTIL::ConstructionValidator const& Simulation::getConstructionValidator()
{
  static ConstructionValidator cv;
  return cv;
}

Simulation::Simulation(DUTIL::ConstructionData const& cd,
                       DUTIL::LoggingSource::LoggingSinkPointer sink) :
    SimulationBase(cd, sink)
{
  this->trace("Default construction of '" + this->getShortConcreteClassName() + "'.");
}
