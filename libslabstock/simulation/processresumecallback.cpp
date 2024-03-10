#include "processresumecallback.h"
#include "process.h"
#include "simulationbase.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_CALLBACK(ProcessResumeCallback)

ConstructionValidator const& ProcessResumeCallback::getConstructionValidator()
{
  using SR = SettingRule;
  // clang-format off
  static const ConstructionValidator cv(
      {SR::forNamedParameter<ProcessResumeCallback::ProcessToResumeId>(
          SR::Usage::MANDATORY_NO_DEFAULT, "Define the id of the process to resume.")},
      {},
      Callback::getConstructionValidator());
  // clang-format on
  return cv;
}

ProcessResumeCallback::ProcessResumeCallback(ConstructionData const& cd) :
    processToResumeId_(
        getConstructionValidator().validateNamedParameter<ProcessResumeCallback::ProcessToResumeId>(
            cd))
{}

ProcessResumeCallback::ProcessResumeCallback(Process const& process) :
    processToResumeId_(process.getId())
{}

void ProcessResumeCallback::callbackImpl(SimulationBase& sim, Event&) const
{
  Process::resume(sim, sim.getEvent<Process>(processToResumeId_));
}
