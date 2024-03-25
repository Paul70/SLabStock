#include "interrupt.h"
#include "process.h"
#include "processinterruptcallback.h"
#include "simulationbase.h"
#include "utility/basictypes.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_EVENT(Interrupt)

Interrupt::Interrupt(ConstructionData const& cd, LoggingSinkPointer sink) :
    Event(cd, sink)
{}

Event::Id Interrupt::newInstance(SimulationBase& sim, DUTIL::ConstructionData cd, Process& target)
{
  D_ASSERT(target.getState() != State::PROCESSED);
  auto interrutpId
      = sim.createEvent(cd.setConcreteClassParameter<Interrupt>().addSubobject<Event::CallbackList>(
          ConstructionData()
              .setConcreteClassParameter<ProcessInterruptCallback>()
              .setParameter<ProcessInterruptCallback::ProcessToInterruptId>(target.getId())));

  // Schedule interrupt with no delay (i.e. tick is 0)
  sim.schedule(interrutpId, Priority::URGENT, 0);
  return interrutpId;
}

std::string Interrupt::whatAmIImpl() const
{
  return Interrupt::getClassName();
}
