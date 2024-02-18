#include "finalize.h"
#include "clearsimulationcallback.h"
#include "simulationbase.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_EVENT(Finalize)

Event::Id Finalize::newInstance(SimulationBase& sim, Delay delay)
{
  // create a Finalize event
  // clang-format off
    auto finalId = sim.createEvent(ConstructionData()
                                    .setConcreteClassParameter<Finalize>()
                                    .setParameter<Event::Description>("This event removes and terminates all events at simualtion end time"));
  //clang-foramt on

  // schedule the Finalize event
  auto& finalEvent = sim.getEvent<Event>(finalId);
  finalEvent.addCallback(ConstructionData().setConcreteClassParameter<ClearSimulationCallback>());

  // schedule Finalize event with priority lazy so that all events scheduled
  // at the same time get still processed.
  sim.schedule(finalId, Priority::LAZY, delay);
  return finalId;
}


Finalize::Finalize(ConstructionData const& cd, LoggingSinkPointer sink) :
    Event(cd, sink)
{}

std::string Finalize::whatAmIImpl() const
{
  return Finalize::getClassName();
}
