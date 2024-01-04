#ifndef SLABSTOCK_SIMULATION_H
#define SLABSTOCK_SIMULATION_H
#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "simulationbase.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zlib.h>

namespace DUTIL {
class ConstructionValidator;
struct ConstructionData;
}  // namespace DUTIL

namespace SLABSTOCK {

/*! \brief description of Simulation
 *
 * Longer description of Simulation.
 */

class Simulation : public SimulationBase, public D_NAMED_CLASS(::SLABSTOCK::Simulation)
{
  public:
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Declare static factory member
  D_DECLARE_SIMULATION(Simulation)

  //! Construct with construction data
  explicit Simulation(DUTIL::ConstructionData const& cd,
                      DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  private:
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_SIMULATION_H
