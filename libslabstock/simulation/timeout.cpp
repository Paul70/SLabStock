#include "timeout.h"
#include "simulationbase.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_EVENT(Timeout)

ConstructionValidator const& Timeout::getConstructionValidator()
{
  using SR = SettingRule;
  static const ConstructionValidator cv(
      {SR::forNamedParameter<Timeout::Delay>(
          SR::Usage::MANDATORY_NO_DEFAULT,
          "Define the delay in time units until this event is triggered.")},
      {}, Event::getConstructionValidator());
  return cv;
}

Event::Id Timeout::newInstance(SimulationBase& sim, Description desc, Delay delay)
{
  // clang-format off
  auto timeoutID = sim.createEvent(ConstructionData().setConcreteClassParameter<Timeout>()
                                                     .setParameter(delay)
                                                     .setParameter(desc)
  );
  // clang-format on
  sim.schedule(timeoutID, Priority::NORMAL, delay);
  return timeoutID;
}

Timeout::Timeout(ConstructionData const& cd, LoggingSinkPointer sink) :
    Event(cd, sink),
    delay_(getConstructionValidator().validateNamedParameter<Timeout::Delay>(cd))
{}

std::string Timeout::whatAmIImpl() const
{
  return Timeout::getClassName();
}
