#include "processfinalizecallback.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_CALLBACK(ProcessFinalizeCallback)

ProcessFinalizeCallback::ProcessFinalizeCallback(ConstructionData const&) {}

void ProcessFinalizeCallback::callbackImpl(SimulationBase& /*sim*/, Event& /*event*/) const {}
