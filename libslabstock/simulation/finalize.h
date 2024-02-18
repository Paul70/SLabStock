#ifndef SLABSTOCK_FINALIZE_H
#define SLABSTOCK_FINALIZE_H
#include "event.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/now.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {
class SimulationBase;

/*! \brief Fianlize event to end a simulation.
 *
 * Longer description of Finalize.
 */

class Finalize final : public Event, public D_NAMED_CLASS(::SLABSTOCK::Finalize)
{
  public:
  //! Static facoty member
  D_DECLARE_EVENT(Finalize)

  //! Define the scheduled time point of the Finalize event.
  D_NAMED_PARAMETER(Delay, DUTIL::Now::Tick)

  //! Inherit ConstructionValidator from Event.
  using Event::getConstructionValidator;

  //! Create and schedule a Finalize event.
  static Event::Id newInstance(SimulationBase& sim, Delay delay);

  //! Construct with construction data
  explicit Finalize(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  private:
  virtual std::string whatAmIImpl() const override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_FINALIZE_H
