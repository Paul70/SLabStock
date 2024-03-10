#ifndef SLABSTOCK_SIMULATION_H
#define SLABSTOCK_SIMULATION_H
#include "simulationbase.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
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
  //! Declare static factory member
  D_DECLARE_SIMULATIONBASE(Simulation)

  //! Inherit ConstructionValidator.
  using SimulationBase::getConstructionValidator;

  //! Construct with construction data.
  explicit Simulation(DUTIL::ConstructionData const& cd,
                      DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  //! Construct an emty simulation.
  Simulation(DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  virtual ~Simulation() override;

  private:
  virtual void runUntilLastEventImpl() override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_SIMULATION_H
