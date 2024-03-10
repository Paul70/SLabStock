#ifndef SLABSTOCK_CLEARSIMULATIONCALLBACK_H
#define SLABSTOCK_CLEARSIMULATIONCALLBACK_H
#include "callback.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of ClearSimulationCallback
 *
 * Longer description of ClearSimulationCallback.
 */

class ClearSimulationCallback final :
    public Callback,
    public D_NAMED_CLASS(::SLABSTOCK::ClearSimulationCallback)
{
  public:
  //! Static facoty member
  D_DECLARE_CALLBACK(ClearSimulationCallback)

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data
  explicit ClearSimulationCallback(DUTIL::ConstructionData const& cd);

  private:
  virtual void callbackImpl(SimulationBase& sim, Event& event) const override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_CLEARSIMULATIONCALLBACK_H
