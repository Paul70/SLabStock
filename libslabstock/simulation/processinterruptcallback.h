#ifndef SLABSTOCK_PROCESSINTERRUPTCALLBACK_H
#define SLABSTOCK_PROCESSINTERRUPTCALLBACK_H
#include "callback.h"
#include "event.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {
class Process;

/*! \brief description of ProcessInterruptCallback
 *
 * Longer description of ProcessInterruptCallback.
 */

class ProcessInterruptCallback final :
    public Callback,
    public D_NAMED_CLASS(::SLABSTOCK::ProcessInterruptCallback)
{
  public:
  //! Static concrete factroy member
  D_DECLARE_CALLBACK(ProcessInterruptCallback)

  //! Define the id of the Process event to interrupt.
  D_NAMED_PARAMETER(ProcessToInterruptId, Event::Id);

  //! Provide validator for construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct directly from a Process instance.
  explicit ProcessInterruptCallback(Process const& process);

  //! Construct with construction data
  explicit ProcessInterruptCallback(DUTIL::ConstructionData const& cd);

  private:
  virtual void callbackImpl(SimulationBase& sim, Event& event) const override;

  Event::Id processToInterruptId_;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_PROCESSINTERRUPTCALLBACK_H
