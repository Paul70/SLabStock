#include "clearsimulationcallback.h"
#include "simulationbase.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_CALLBACK(ClearSimulationCallback)

ClearSimulationCallback::ClearSimulationCallback([[maybe_unused]] ConstructionData const& cd) {}

void ClearSimulationCallback::callbackImpl(SimulationBase& sim, Event&) const
{
  std::vector<Event::Id> allEvents;

  // iterate over all not scheduled events
  // and gather their ids.
  sim.iterate<Event>([&](Event const& e) { allEvents.push_back(e.getId()); });

  // clear all simulation events from the queue scheduled later as delay.
  sim.clearQueue();

  // call the finalize function for each event
  for (auto eventId : allEvents) {
    auto& event = sim.getEvent<Event>(eventId);
    event.finalize(sim);
  }
}
