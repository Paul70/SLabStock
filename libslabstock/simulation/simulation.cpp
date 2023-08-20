#include "simulation.h"

using namespace DUTIL;
using namespace SLABSTOCK;

Simulation::Simulation(DUTIL::ConstructionData const &cd, DUTIL::LoggingSource::LoggingSinkPointer sink) :
    SimulationBase(cd, sink)
{
    this->trace("Default construction of '" + this->getShortConcreteClassName() + "'.");
}
