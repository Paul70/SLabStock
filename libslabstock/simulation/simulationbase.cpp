#include "simulationbase.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_FACTORYINTERFACE(::SLABSTOCK::SimulationBase)

std::list<std::string> SimulationBase::simulations_{};

bool SimulationBase::ckeckId(SimulationBase::Id const newId)
{
  if (std::find(simulations_.cbegin(), simulations_.cend(), newId.value()) == simulations_.cend())
    return true;
  else
    return false;
}

ConstructionValidator const& SimulationBase::getConstructionValidator()
{
  using SR = SettingRule;
  using WR = WarelistRule;
  static const ConstructionValidator cv(
      {SR::forNamedParameter<SimulationBase::Id>(SR::Usage::OPTIONAL,
                                                 "Set the simulation Id. If no Id is given, we "
                                                 "will use the address of this object as Id."),
       []() {
         SR sr = SR::forNamedParameter<SimulationBase::StartTime_ms>(
             SR::Usage::MANDATORY_WITH_DEFAULT,
             "Define what the simulation reports as absolute time and set the simulation start "
             "time point with respect to a std::chrono clock. This parameter is especially "
             "important for real time simulations. See RealTimeSimulation class.");
         sr.defaultValue = 0;
         return sr;
       }(),
       []() {
         SR sr = SR::forNamedParameter<SimulationBase::StartTick>(
             SR::Usage::MANDATORY_WITH_DEFAULT,
             "Define the start time tick. A time tick is an integer counter which will be "
             "increased every time the simulation advnances in time by any step. A time tick "
             "corresponds to a real time point.");
         sr.defaultValue = 0;
         return sr;
       }()},
      {WR::forSubobjectList<SimulationBase::EventList>(
          "Define all currently registered events for this simulation.")},
      ProjectWare::getConstructionValidator());
  return cv;
}

SimulationBase::SimulationBase(DUTIL::ConstructionData const& cd,
                               LoggingSource::LoggingSinkPointer sink) :
    LoggingSource(sink),
    id_(getConstructionValidator().validateNamedParameter<SimulationBase::Id>(cd)),
    eventMap_(),
    eventQueue_(),
    startTime_ms_(
        getConstructionValidator().validateNamedParameter<SimulationBase::StartTime_ms>(cd)),
    startTick_(getConstructionValidator().validateNamedParameter<SimulationBase::StartTick>(cd))
{
  if (id_.value().empty()) {
    std::ostringstream stream;
    stream << this;
    id_ = stream.str();
  }
  if (!ckeckId(id_)) {
    D_THROW("Simulation Id '" + id_.value() + "' already in use and not unique.");
  } else {
    simulations_.emplace_back(id_);
  }

  auto eventlist = getConstructionValidator().buildSubobjectList<SimulationBase::EventList>(cd);
  for (auto&& event : eventlist) {
    event->setLoggingSink(this->getLoggingSink());
    eventMap_.emplace(event->getId(), std::move(event));
  }

  // hier muss ich alle events noch schedulen via insert

  this->trace("Finished construction of '" + FactoryInterface<SimulationBase>::getInterfaceName()
              + "'.");
}

std::uint64_t SimulationBase::getStartTime_ms() const
{
  return startTime_ms_;
}

SimulationBase::Id SimulationBase::getId() const
{
  return id_;
}

bool SimulationBase::isEmpty() const
{
  return eventQueue_.empty();
}

void SimulationBase::schedule(const Event::Id id, const Priority priority, const Now::Tick tick)
{
  auto& event = getEvent(id);
  event.advanceState();
  eventQueue_.emplace(std::make_pair(tick, priority.value()), id);

  this->debug("Scheduled event '" + event.whatAmI() + "' at time tick step "
              + Utility::toString(tick) + " with priority " + priority.toString());
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

  this->trace("Creation of new event with Id: " + Utility::toString(newId));
  return newId;
}

void SimulationBase::logEventList() const
{
  logEventListImpl();
}
