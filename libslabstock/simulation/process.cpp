#include "process.h"
#include "initialize.h"
#include "interrupt.h"
#include "processinitializecallback.h"
#include "processresumecallback.h"
#include "simulationbase.h"
#include "timeout.h"

#include "libd/libdutil/constructionvalidator.h"

using namespace SLABSTOCK;

D_DEFINE_FACTORYINTERFACE(::SLABSTOCK::Process)

using namespace DUTIL;

namespace SLABSTOCK {}  // namespace SLABSTOCK

ConstructionValidator const& Process::getConstructionValidator()
{
  using SR = SettingRule;
  static const ConstructionValidator cv(
      {[]() {
        SR sr = SR::forNamedParameter<Process::TargetId>(
            SR::Usage::MANDATORY_WITH_DEFAULT,
            "Define the id of the event this process is currently waiting for.");
        sr.defaultValue = -1;  // This value will be set by ProcessIninitializeCallback.
        return sr;
      }()},
      {}, Event::getConstructionValidator());
  return cv;
}

ConstructionData const& Process::getDefaultConstructionData()
{
  static const ConstructionData cd(ConstructionData().setParameter<Process::Description>(
      "Default ConstructionData to build processes with no further, derived specifications."));
  return cd;
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

Process::Id Process::initWithParent(SimulationBase& sim, DUTIL::ConstructionData process_cd)
{
  auto processDescription
      = Process::getConstructionValidator().validateNamedParameter<Event::Description>(process_cd);

  auto timeoutId = Timeout::newInstance(sim, "trigger event for " + processDescription.value(), 0);
  Timeout& timeout = sim.getEvent<Timeout>(timeoutId);
  auto processId = sim.createEvent(process_cd.setParameter<Process::TargetId>(timeoutId));
  timeout.addCallback(ConstructionData()
                          .setParameter<ProcessResumeCallback::ProcessToResumeId>(processId)
                          .setConcreteClassParameter<ProcessResumeCallback>());

  return processId;
}

void Process::resume(SimulationBase& sim, Process& process)
{
  Event::Id nextEventId;
  bool finished = process.update(sim, nextEventId);
  if (finished) {
    // Porcess is done, schedule it in turn, one last time
    sim.schedule(process.getId());
    return;
  }

  // clang-format off
  process.debug("Process with id "
                + Utility::toString(process.getId())
                + " '"
                + process.getDescription()
                + "' has updated, is now waiting for event id "
                + Utility::toString(nextEventId)
                + " '"
                + sim.getEvent<Event>(nextEventId).getDescription()
                 + "'");
  // clang-format on

  // this process is now waiting for process with id nextEventId to happend
  // or in other words, when event with nextEventId happens, process p is called again.
  process.targetId_ = nextEventId;

  // Therefore, the target porcess needs a callback to resume this porcess again.
  process.getTarget(sim).addCallback(
      ConstructionData()
          .setConcreteClassParameter<ProcessResumeCallback>()
          .setParameter<ProcessResumeCallback::ProcessToResumeId>(process.getId()));
}

void Process::interrupt(SimulationBase& sim, Process& process, Interrupt& interrupt)
{
  // Ignore finished processes.
  if (process.getState() == State::PROCESSED)
    return;

  Event::Id nextEventId = -1;

  // call the concrete process' interrupt method telling what to do when an interrupt happens.
  bool finished = process.interruptImpl(sim, interrupt, nextEventId);

  // Process ignored interrupt and has terminated.
  if (finished)
    return;

  // clang-format off
  process.debug("Process with id "
                + Utility::toString(process.getId())
                + " '"
                + process.getDescription()
                + "' recovered from interruption, is now waiting for '"
                + sim.getEvent<Event>(nextEventId).getDescription()
                + "' with id "
                + Utility::toString(nextEventId));
  // clang-format on

  // set a new target for this process and create a new ProcessResumeCallback.
  // Each process has a target to wait for. When this target porcess has happend, this process
  // starts executing again. Therefore, we nees to add a ProcessResumeCallback to the target process.
  process.targetId_ = nextEventId;
  process.getTarget(sim).addCallback(
      ConstructionData()
          .setParameter<ProcessResumeCallback::ProcessToResumeId>(process.getId())
          .setConcreteClassParameter<ProcessResumeCallback>());
}

Process::Process(ConstructionData const& cd, LoggingSinkPointer sink) :
    Event(cd, sink)
{}

Event& Process::getTarget(SimulationBase& sim) const
{
  return sim.getEvent<Process>(this->targetId_);
}

bool Process::update(SimulationBase& sim, Event::Id& newTarget)
{
  return updateImpl(sim, newTarget);
}

bool Process::interruptImpl(SimulationBase&, Interrupt& i, Event::Id&)
{
  warn("Process with id " + Utility::toString(getId()) + " '" + getDescription()
       + "' did not handle Interruption id " + Utility::toString(i.getId()) + " '"
       + i.getDescription() + "'");
  return true;
}
