#include "processinterruptcallback.h"
#include "interrupt.h"
#include "process.h"
#include "simulationbase.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_CALLBACK(ProcessInterruptCallback)

ConstructionValidator const& ProcessInterruptCallback::getConstructionValidator()
{
  using SR = SettingRule;
  static const ConstructionValidator cv({SR::forNamedParameter<ProcessToInterruptId>(
      SR::Usage::MANDATORY_NO_DEFAULT, "Define the id of the Process to interrupt.")});
  return cv;
}

ProcessInterruptCallback::ProcessInterruptCallback(ConstructionData const& cd) :
    processToInterruptId_(
        getConstructionValidator()
            .validateNamedParameter<ProcessInterruptCallback::ProcessToInterruptId>(cd))
{}

void ProcessInterruptCallback::callbackImpl(SimulationBase& sim, Event& event) const
{
  return Process::interrupt(sim, sim.getEvent<Process>(processToInterruptId_),
                            dynamic_cast<Interrupt&>(event));
}
