#ifndef SLABSTOCK_PROCESSRESUMECALLBACK_H
#define SLABSTOCK_PROCESSRESUMECALLBACK_H
#include "callback.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "simulation/event.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {
class Process;

class ProcessResumeCallback final :
    public Callback,
    public D_NAMED_CLASS(::SLABSTOCK::ProcessResumeCallback)
{
  public:
  //! Static concrete factroy member
  D_DECLARE_CALLBACK(ProcessResumeCallback)

  //! Define the Id of the porcess to resume.
  D_NAMED_PARAMETER(ProcessToResumeId, Event::Id)

  //! Define the rules of construction for this class.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data
  explicit ProcessResumeCallback(DUTIL::ConstructionData const& cd);

  //! Construct directly from a Process instance.
  explicit ProcessResumeCallback(Process const& process);

  private:
  virtual void callbackImpl(SimulationBase& sim, Event& event) const override;

  Event::Id processToResumeId_;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_PROCESSRESUMECALLBACK_H
