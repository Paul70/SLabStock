#include "simulationbase.h"
#include "finalize.h"

#include "libd/libdutil/constructionvalidator.h"
#include "simulation/callback.h"

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

  // schedule given events due to information given in ConstructionData data set
  // each dataset row contains scheduling information for one event.
  // Dataset has three columns:
  // - 1. col: event id;
  // - 2. col: event priority
  // - 3. col: event tick
  auto rows = cd.ds.getRows();
  for (auto row = 0; row < rows; ++row) {
    auto values = cd.ds.getValues<Now::Tick>();
    schedule(values[0], Priority(values[1]), values[2]);
  }

  this->trace("Finished construction of '" + FactoryInterface<SimulationBase>::getInterfaceName()
              + "'.");

  logEventMap(LoggingSink::LogSeverity::TRACE);
}

SimulationBase::~SimulationBase()
{
  auto success = removeId();
  D_ASSERT(success);
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

Now::Tick SimulationBase::now() const
{
  return now_;
}

std::int64_t SimulationBase::peekNextEvent() const
{
  if (eventQueue_.empty()) {
    return -1;
  }
  return eventQueue_.cbegin()->second;
}

Event::Id SimulationBase::getNextEvent() const
{
  D_ASSERT(!eventQueue_.empty());
  return eventQueue_.cbegin()->second;
}

void SimulationBase::schedule(const Event::Id id, const Priority priority, const Now::Tick tick)
{
  // put events into the event queue.
  auto& event = getEvent(id);
  event.advanceState();
  auto eventTick = now() + tick;
  eventQueue_.emplace(std::make_pair(eventTick, priority.value()), id);

  this->debug("Scheduled event '" + event.whatAmI() + "' at time tick step "
              + Utility::toString(eventTick) + " with priority " + priority.toString());
}

void SimulationBase::clearQueue()
{
  for (auto iter = eventQueue_.begin(); iter != eventQueue_.end();) {
    if (iter->first.first <= static_cast<unsigned long>(now_))
      ++iter;
    else {
      auto eventId = iter->second;
      debug("Removing upcoming event id " + Utility::toString(eventId) + " '"
            + getEvent(eventId).getDescription() + "' scheduled at "
            + Utility::toString(iter->first.first) + " from queue.");
      iter = eventQueue_.erase(iter);
    }
  }
}

Event::Id SimulationBase::runUntil(DUTIL::Now::Tick until)
{
  D_ASSERT(until > static_cast<unsigned long>(now_));

  // create and schedule a Finalize event
  auto id = Finalize::newInstance(*this, until - now_);
  runUntilLastEvent();
  return id;
}

void SimulationBase::runUntilLastEvent()
{
  runUntilLastEventImpl();
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

  this->debug("Creation of new event with Id: " + Utility::toString(newId)
              + ". \nEvent type: " + event->whatAmI());

  eventMap_[newId] = std::move(event);
  return newId;
}

Event::Id SimulationBase::step()
{
  // Calling this function in case of an empty event queue is forbidden.
  D_ASSERT(!eventQueue_.empty());
  auto item = eventQueue_.cbegin();
  now_ = item->first.first;

  auto eventId = item->second;
  auto& event = getEvent(eventId);
  event.advanceState();

  // log message

  // call each callback registered for the current event
  for (auto& cb : event.takeCallbacks()) {
    // log message

    (*cb)(*this, event);
  }

  // log message
  event.advanceState();
  eventMap_.erase(eventId);
  eventQueue_.erase(item);
  return eventId;
}

void SimulationBase::logEventMap(LoggingSink::LogSeverity level, std::string_view filter) const
{
  this->log("List of curretntly mapped simulation events:", level);
  std::string list{};

  for (auto& event : eventMap_) {
    if (!filter.empty()
        && (Utility::toString(event.first).find(filter) || event.second->whatAmI().find(filter))) {
      list.append("Event Id: " + Utility::toString(event.first) + '\t'
                  + "Type: " + event.second->whatAmI() + '\n');
    }
  }

  this->log(list, level);
}

bool SimulationBase::removeId() const
{
  auto iterator = std::find(simulations_.cbegin(), simulations_.cend(), id_.value());
  if (iterator != simulations_.cend()) {
    simulations_.erase(iterator);
    return true;
  }
  return false;
}
