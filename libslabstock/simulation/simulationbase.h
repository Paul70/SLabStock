#ifndef SLABSTOCK_SIMULATIONBASE_H
#define SLABSTOCK_SIMULATIONBASE_H
#include "event.h"
#include "libslabstock/utility/basictypes.h"

#include "libd/libdutil/namedreference.h"
#include "libd/libdutil/projectware.h"
#include "libd/libdutil/ticker.h"
#include "libd/libdutil/time.h"

#include <functional>
#include <list>
#include <map>

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {

/*! \brief description of SimulationBase
 *
 * Longer description of SimulationBase.
 */
class SimulationBase : public DUTIL::ProjectWare, public DUTIL::LoggingSource
{
  public:
  //! Define a map containing all events currently participating in a simulation.
  using EventMap = std::map<Event::Id, std::unique_ptr<Event>>;

  //! Key type to identify an event inside an event queue.
  using QueueKey = std::pair<DUTIL::Ticker::Tick, Priority>;

  //! Ticker type to indicate/count simulation progress.
  using SimTicker = std::unique_ptr<DUTIL::Ticker>;

  /*! \brief Map container for all currently existing simulation events.
   *
   * One event is identified by the time point it starts happening and its priority.
   * Events starting at the same time and having the same priority get processed due to first in
   * first out.
   * Objects of this type contain the event schedule.
   */
  using Queue = std::multimap<QueueKey, Event::Id>;

  //! Define a simulation id to identify a concrete simulation object later.
  D_NAMED_STRING(Id);

  //! Set of simulation events.
  D_NAMED_REFERENCE(EventList, Event)

  //! Event ticker tracking progress of simulation by increasing a counter.
  D_NAMED_REFERENCE(EventTicker, DUTIL::Ticker)

  /*! \brief Check if choosen Id is already used.
   *
   * Returns true if Id is ok, ohterwise, if Id is already in use
   * returns false.
   */
  static bool ckeckId(SimulationBase::Id const newId);

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Constructor using ConstructionData.
  explicit SimulationBase(DUTIL::ConstructionData const& cd,
                          DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  virtual ~SimulationBase();

  //! Retrun the absolute start time as a Unix timestamp in milli secconds.
  std::uint64_t getStartTime_ms() const;

  //! Return the time resolution.
  DUTIL::real_t getTimeTickResolution() const;

  //! Return the elapsed simulation time in seconds.
  DUTIL::real_t getElapsedSimulatedTime() const;

  //! Retrun simualtion Id.
  SimulationBase::Id getId() const;

  //! Return if the schedule is empty.
  bool isEmpty() const;

  //! Return the current time tick.
  DUTIL::Ticker::Tick now() const;

  /*! \brief Get the time tick of the next scheduled event.
   *
   * Assert that schedule is not empty.
   */
  DUTIL::Ticker::Tick peekNext() const;

  /*! \brief Get the time in seconds of the next scheduled event.
   *
   * Assert that schedule is not empty.
   */
  DUTIL::TIME::basic_sec_t peekNextTime(DUTIL::TIME::UnitPrefix prefix
                                        = DUTIL::TIME::UnitPrefix::SECONDS) const;

  /*! \brief Get the tick of the final scheduled event.
   *
   * Assert that schedule is not empty.
   */
  DUTIL::Ticker::Tick peekLast() const;

  /*! \brief Return a copy of the event id of the next scheduled event.
   *
   * If the queue is empty, return -1;
   */
  std::int64_t peekNextEvent() const;

  /*! \brief Return the Id of the next scheduled event.
   *
   * Assert if event queue is empty.
   */
  Event::Id getNextEvent() const;

  /*! \brief Put or re-put an event into the simulation event Queue.
   *
   * According to the event queue key, place the event into the queue.
   */
  void schedule(const Event::Id id, const Priority piority = Priority::NORMAL,
                const DUTIL::Ticker::Tick tick = 0);

  //! Remove all events from queue scheduled at times > now().
  void clearQueue();

  /*! \brief Run until input time tick is reached
   *
   * Starts the simulation and steps through the event queue until
   * the given time tick. The time tick counter gets increased everytime the simualtion's
   * step() function is called.
   */
  Event::Id runUntil(DUTIL::Ticker::Tick until);

  //! Run the simulation until the last, scheduled event is fully processed and finalized.
  void runUntilLastEvent();

  //! Generate an event Id not in use.
  Event::Id getUnusedEventId() const;

  Event::Id createEvent(DUTIL::ConstructionData cd);

  /*! \brief Retrieve a concrete event from the event map.
   *
   * Assert if the event id does not exist.
   */
  template <typename ConcreteEvent = Event,
            std::enable_if_t<EventDetail::is_event_v<ConcreteEvent>, bool> = false>
  ConcreteEvent& getEvent(const Event::Id id) const
  {
    try {
      auto& event = eventMap_.at(id);
      return static_cast<ConcreteEvent&>(*event);
      //auto& result = dynamic_cast<ConcreteEvent&>(*event.get());
      //return result;
    } catch (...) {
      this->fatal("Rquested event with Id '" + DUTIL::Utility::toString(id)
                  + "' does not exist. Terminating program.");
      D_ASSERT(false);
    };
  }

  /*! \brief Log all currently mapped events.
   *
   * If no event is mapped, emtpy string will be written to stream.
   * Define a filter string for the event name or Id.
   */
  void logEventMap(DUTIL::LoggingSink::LogSeverity level, std::string_view filter = {}) const;

  /*! \brief Call given functor for all unscheduled Events of given type.
   *
   * tbd
   */
  template <typename ConcreteEvent = Event>
  void iterate(std::function<void(ConcreteEvent const& event)> functor)
  {
    for (auto const& e : eventMap_) {
      if (e.second->getState() != Event::State::NOT_SCHEDULED) {
        continue;
      }
      auto const* ce = dynamic_cast<ConcreteEvent const*>(e.second.get());
      if (!ce)
        continue;
      functor(*ce);
    }
  }

  protected:
  Event::Id step();

  private:
  virtual void runUntilLastEventImpl() = 0;

  // Delete current simualtion id from the list of present simulation objects at destruction.
  bool removeId() const;

  Id id_;
  SimTicker ticker_;
  EventMap eventMap_;
  Queue eventQueue_;

  static std::list<std::string> simulations_;
};
}  // namespace SLABSTOCK

D_DECLARE_FACTORYINTERFACE(::SLABSTOCK::SimulationBase)

#define D_DECLARE_SIMULATIONBASE(REGISTERED_CLASS)                                 \
  static const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::SimulationBase, \
                                      DUTIL::ProjectWare>                          \
      factory;

#define D_DEFINE_SIMULATIONBASE(REGISTERED_CLASS)                                               \
  const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::SimulationBase, DUTIL::ProjectWare> \
      REGISTERED_CLASS::factory;

#endif  // SLABSTOCK_SIMULATIONBASE_H
