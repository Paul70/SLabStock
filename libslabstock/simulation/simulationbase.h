#ifndef SLABSTOCK_SIMULATIONBASE_H
#define SLABSTOCK_SIMULATIONBASE_H
#include "event.h"
#include "libslabstock/utility/basictypes.h"

#include "libd/libdutil/namedreference.h"
#include "libd/libdutil/now.h"
#include "libd/libdutil/projectware.h"

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
  using QueueKey = std::pair<DUTIL::Now::Tick, Priority>;

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

  //! Parameter holding the start tick value.
  D_NAMED_PARAMETER(StartTick, DUTIL::Now::Tick)

  //! Parameter holding the start time in milli seconds.
  D_NAMED_PARAMETER(StartTime_ms, DUTIL::Now::Tick)

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

  //! Retrun the absolute start time as a Unix timestamp in milli secconds.
  std::uint64_t getStartTime_ms() const;

  //! Retrun simualtion Id.
  SimulationBase::Id getId() const;

  //! Return if the schedule is empty.
  bool isEmpty() const;

  /*! \brief Put or re-put an event into the simulation event Queue.
   *
   * According to the event queue key, place the event into the queue.
   */
  void schedule(const Event::Id id, const Priority piority = Priority::NORMAL,
                const DUTIL::Now::Tick tick = 0);

  //! Generate an event Id not in use.
  Event::Id getUnusedEventId() const;

  Event::Id createEvent(DUTIL::ConstructionData cd);

  // next steps:
  // wichtige function for simulation machen
  // erstes Beispiel zum Laufen bekommen
  // initialize und finalize implementieren
  // process weiter implementieren

  // wie mache ich weiter:
  // über die events steppen

  // danach das erste Beispiel bauen

  protected:
  Event::Id step();

  void logEventList() const;

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
      return dynamic_cast<ConcreteEvent&>(*event);
    } catch (...) {
      this->fatal("Rquested event with Id '" + DUTIL::Utility::toString(id)
                  + "' does not exist. Terminating program.");
      D_ASSERT(false);
    };
  }

  private:
  virtual void logEventListImpl() const = 0;

  Id id_;
  EventMap eventMap_;
  Queue eventQueue_;
  DUTIL::Now::Tick startTime_ms_;
  DUTIL::Now::Tick startTick_;
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
