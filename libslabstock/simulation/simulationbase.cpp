#include "simulationbase.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_FACTORYINTERFACE(::SLABSTOCK::SimulationBase)

bool SimulationBase::ckeckId(SimulationBase::Id const newId)
{
  if (std::find(simulations.cbegin(), simulations.cend(), newId.value()) == simulations.cend())
    return true;
  else
    return false;
}

const ConstructionValidator SimulationBase::getConstructionValidator()
{
  using SR = SettingRule;
  using WR = WarelistRule;
  static const ConstructionValidator cv(
      {SR::forNamedParameter<SimulationBase::Id>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                 "Set the simulation Id.")},
      {WR::forSubobjectList<SimulationBase::EventList>(
          "Define all currently registered events for this simulation.")});
  return cv;
}

SimulationBase::SimulationBase(DUTIL::ConstructionData const& cd,
                               LoggingSource::LoggingSinkPointer sink) :
    LoggingSource(sink),
    id_(getConstructionValidator().validateNamedParameter<SimulationBase::Id>(cd)),
    eventMap_(),
    eventQueue_(),
    now_()
{
  if (!ckeckId(id_)) {
    D_THROW("Simulation Id '" + id_.value() + "' already in use and not unique.");
  } else {
    simulations.emplace_back(id_);
  }

  auto eventlist = getConstructionValidator().buildSubobjectList<SimulationBase::EventList>(cd);
  for (auto&& event : eventlist) {
    event->setLoggingSink(this->getLoggingSink());
    eventMap_.emplace(event->getId(), std::move(event));
  }

  this->trace("Default construction of '" + ProjectWare::getShortConcreteClassName() + "'.");
}

SimulationBase::Id SimulationBase::getId() const
{
  return id_;
}

Event::Id SimulationBase::getUnusedEventId() const
{
  if (eventMap_.empty()) {
    return 0;
  }
  return ((--eventMap_.cend())->first) + 1;
}

Event::Id SimulationBase::createEvent(ConstructionData cd)
{
  const Event::Id newId = getUnusedEventId();
  cd.setParameter<Event::IdParam>(newId);
  auto event = FactoryInterface<Event>::newInstanceViaTypeSetting(cd);
  event->setLoggingSink(getLoggingSink());
  eventMap_[newId] = std::move(event);
  return newId;
}
