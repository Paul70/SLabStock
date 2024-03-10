#ifndef SLABSTOCK_REALTIMESIMULATION_H
#define SLABSTOCK_REALTIMESIMULATION_H
#include "simulationbase.h"
#include "simulationsignaler.h"

#include "libd/libdutil/namedclass.h"

namespace DUTIL {
class Clock;
struct ConstructionData;
}  // namespace DUTIL

namespace SLABSTOCK {

/*! \brief description of RealTimeSimulation
 *
 * Longer description of RealTimeSimulation.
 */

class RealTimeSimulation final :
    public SimulationBase,
    public SimulationSignaler,
    public D_NAMED_CLASS(::SLABSTOCK::RealTimeSimulation)
{
  public:
  using SimClock = std::unique_ptr<DUTIL::Clock>;

  //! static factory member.
  D_DECLARE_SIMULATIONBASE(RealTimeSimulation);

  //! Define the clock object to measure real time.
  D_NAMED_REFERENCE(RealTime, DUTIL::Clock)

  //! Define the tolerance in seconds as described above..
  D_NAMED_REAL(Tolerance_s)

  //! Provide validator for construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data.
  explicit RealTimeSimulation(DUTIL::ConstructionData const& cd,
                              DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  //! Construct an empty real time simulation with nothing scheduled.
  explicit RealTimeSimulation(DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  //! Implemented destructor due to forward declaring unique pointer type.
  ~RealTimeSimulation();

  private:
  virtual void runUntilLastEventImpl() override;
  virtual void startSimulationImpl() override;
  virtual void stopSimulationImpl() override;
  virtual void stepAndDelayImpl(bool doStep) override;

  SimClock clock_;
  DUTIL::real_t tolerance_s_;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_REALTIMESIMULATION_H
