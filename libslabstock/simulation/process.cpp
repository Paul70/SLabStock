#include "process.h"
#include "initialize.h"
#include "processinitializecallback.h"
#include "simulationbase.h"

#include "libd/libdutil/constructionvalidator.h"

using namespace SLABSTOCK;

D_DEFINE_FACTORYINTERFACE(::SLABSTOCK::Process)

using namespace DUTIL;

namespace SLABSTOCK {}  // namespace SLABSTOCK

ConstructionValidator const& Process::getConstructionValidator()
{
  static const ConstructionValidator cv;
  return cv;
}

void Process::init(SimulationBase& sim, DUTIL::ConstructionData const& process_cd)
{
  auto processDescription
      = Process::getConstructionValidator().validateNamedParameter<Event::Description>(process_cd);

  // create and schedule an initialize event.
  // clang-foramt off
  auto init_id = sim.createEvent(
      ConstructionData()
          .setConcreteClassParameter<Initialize>()
          .setParameter<Event::Description>("Init event for " + processDescription.value())
          .addSubobject<Initialize::CallbackList>(
              ConstructionData().setConcreteClassParameter<ProcessInitializeCallback>())
          .addSubobject<Initialize::ProcessToStart>(process_cd));
  // clang-foramt on

  sim.schedule(init_id);
}

Process::Process(ConstructionData const& cd, LoggingSinkPointer sink) :
    Event(cd, sink)
{}

bool Process::update(SimulationBase& sim, Event::Id& newTarget)
{
  return updateImpl(sim, newTarget);
}
