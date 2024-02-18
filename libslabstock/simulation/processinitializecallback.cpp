#include "processinitializecallback.h"
#include "initialize.h"
#include "simulationbase.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_CALLBACK(ProcessInitializeCallback)

ProcessInitializeCallback::ProcessInitializeCallback(ConstructionData const&) {}

void ProcessInitializeCallback::callbackImpl(SimulationBase& sim, Event& event) const
{
  // this is the actual process ConstructionData to initialize by this
  // Initialize event.
  auto cdProcess = Initialize::getProcessCD(event);

  // now set the the process target id
  // That is, tell the Process in his ConstructionData for which event he waits to happen.
  // The happening of this target event is the prerequisite for this process to start executing.
  // In this case, the process cannot start executing, until its initialize event took place.
  cdProcess.setParameter<Process::TargetId>(event.getId());

  // Create the actual process as part of the simulation.
  auto processId = sim.createEvent(cdProcess);
  auto& process = sim.getEvent<Process>(processId);

  Process::resume(sim, process);
}
