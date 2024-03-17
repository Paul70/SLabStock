#ifndef SLABSTOCK_TIMEOUT_H
#define SLABSTOCK_TIMEOUT_H
#include "event.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/ticker.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {
class SimulationBase;

/*! \brief description of Timeout
 *
 * Longer description of Timeout.
 */

class Timeout : public Event, public D_NAMED_CLASS(::SLABSTOCK::Timeout)
{
  public:
  D_DECLARE_EVENT(Timeout);

  D_NAMED_PARAMETER(Delay, DUTIL::Ticker::Tick);

  static DUTIL::ConstructionValidator const& getConstructionValidator();

  static Event::Id newInstance(SimulationBase& sim, Description desc, Delay delay);

  //! Construct with construction data
  explicit Timeout(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  private:
  virtual std::string whatAmIImpl() const override;

  DUTIL::Ticker::Tick delay_;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_TIMEOUT_H
