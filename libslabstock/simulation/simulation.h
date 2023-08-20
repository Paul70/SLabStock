#ifndef SLABSTOCK_SIMULATION_H
#define SLABSTOCK_SIMULATION_H
#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "simulationbase.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of Simulation
 *
 * Longer description of Simulation.
 */

class Simulation : public SimulationBase, public D_NAMED_CLASS(::SLABSTOCK::Simulation)
{
public:
    //! Declare static factory member
    D_DECLARE_PROJECTWARE(Simulation)

    //! Construct with construction data
    explicit Simulation(DUTIL::ConstructionData const &cd, DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

private:
};

} // namespace SLABSTOCK
#endif // SLABSTOCK_SIMULATION_H
