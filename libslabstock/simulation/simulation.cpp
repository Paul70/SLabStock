#include "simulation.h"

//#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;

namespace SLABSTOCK {

D_DEFINE_SIMULATIONBASE(Simulation)

Simulation::Simulation(ConstructionData const& cd, LoggingSource::LoggingSinkPointer sink) :
    SimulationBase(cd, sink)
{
  this->trace("Finished construction of '" + this->getShortConcreteClassName()
              + "' with ConstructionData.");
}

Simulation::Simulation(DUTIL::LoggingSource::LoggingSinkPointer sink) :
    SimulationBase(ConstructionData{}, sink)
{
  this->trace("Finished construction of '" + this->getShortConcreteClassName()
              + "' without ConstructionData.");
}

void Simulation::logEventListImpl() const {}
}  // namespace SLABSTOCK
