#ifndef SLABSTOCK_PROCESSINITIALIZECALLBACK_H
#define SLABSTOCK_PROCESSINITIALIZECALLBACK_H
#include "callback.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of ProcessInitializeCallback
 *
 * Longer description of ProcessInitializeCallback.
 */

class ProcessInitializeCallback final :
    public Callback,
    public D_NAMED_CLASS(::SLABSTOCK::ProcessInitializeCallback)
{
  public:
  //! Static factory
  D_DECLARE_CALLBACK(ProcessInitializeCallback)

  //! Construct with construction data
  explicit ProcessInitializeCallback(DUTIL::ConstructionData const& cd);

  private:
  virtual void callbackImpl(SimulationBase& sim, Event& event) const override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_PROCESSINITIALIZECALLBACK_H
