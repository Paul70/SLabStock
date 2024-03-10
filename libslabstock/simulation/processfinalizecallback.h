#ifndef SLABSTOCK_PROCESSFINALIZECALLBACK_H
#define SLABSTOCK_PROCESSFINALIZECALLBACK_H
#include "callback.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of ProcessFinalizeCallback
 *
 * Longer description of ProcessFinalizeCallback.
 */

class ProcessFinalizeCallback final :
    public Callback,
    public D_NAMED_CLASS(::SLABSTOCK::ProcessFinalizeCallback)
{
  public:
  //! Static factroy member.
  D_DECLARE_CALLBACK(ProcessFinalizeCallback)

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data
  explicit ProcessFinalizeCallback(DUTIL::ConstructionData const& cd);

  private:
  virtual void callbackImpl(SimulationBase& sim, Event& event) const override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_PROCESSFINALIZECALLBACK_H
