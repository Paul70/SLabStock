#ifndef SLABSTOCK_INTERRUPT_H
#define SLABSTOCK_INTERRUPT_H
#include "event.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {
class Process;

/*! \brief Immediately schedule an exception-like event to be passed to a given Process.
 *
 * An Interruption is automatically scheduled on creation.
 */

class Interrupt final : public Event, public D_NAMED_CLASS(::SLABSTOCK::Interrupt)
{
  public:
  //! Static concrete factroy member
  D_DECLARE_EVENT(Interrupt)

  //! Define an optional text for the cause of the interruption.
  D_NAMED_STRING(Cause)

  //! Construct with construction data
  explicit Interrupt(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  /*! \brief Create and immediately schedule an interrupt event.
   *
   * An interrupt event has a ProcessInterruptCallback. The interrupt event gets scheduled immediately
   * with priority URGENT and we call its ProcessInterruptCallback. This callback calls the
   * interrupt() method of the target process.
   */
  static Event::Id newInstance(SimulationBase& sim, DUTIL::ConstructionData cd, Process& target);

  private:
  virtual std::string whatAmIImpl() const override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_INTERRUPT_H
