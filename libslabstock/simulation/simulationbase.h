#ifndef DUTIL_SIMULATIONBASE_H
#define DUTIL_SIMULATIONBASE_H
#include "event.h"
#include "utility/basictypes.h"

#include "libd/libdutil/namedreference.h"
#include "libd/libdutil/now.h"
#include "libd/libdutil/projectware.h"

#include <list>
#include <map>
#include <tuple>

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
  using QueueKey = std::pair<TimeTick, Priority>;

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

  //! Check if choosen Id is not already used.
  /*! \brief Check if choosen Id is already used.
   *
   * Returns true if Id is ok, ohterwise, if Id is already in use
   * returns false.
   */
  static bool ckeckId(SimulationBase::Id const newId);

  //! Return construction requirements.
  static const DUTIL::ConstructionValidator getConstructionValidator();

  //! Constructor.
  explicit SimulationBase(DUTIL::ConstructionData const& cd,
                          DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  //! Retrun simualtion Id.
  SimulationBase::Id getId() const;

  void schedule();

  //! Generate an event Id not in use.
  Event::Id getUnusedEventId() const;

  Event::Id createEvent(DUTIL::ConstructionData cd);

  // next steps:
  // wichtige function for simulation machen
  // erstes Beispiel zum Laufen bekommen
  // initialize und finalize implementieren
  // process weiter implementieren

  // wie mache ich weiter:
  // queue jetzt bauen, also schedule machen und dann
  // über die events steppen

  // danach das erste Beispiel bauen

  protected:
  Event::Id step();

  private:
  Id id_;
  EventMap eventMap_;
  Queue eventQueue_;
  DUTIL::Now now_;

  static std::list<std::string> simulations;
};
}  // namespace SLABSTOCK

D_DECLARE_FACTORYINTERFACE(::SLABSTOCK::SimulationBase)

#define D_DECLARE_SIMULATION(REGISTERED_CLASS)                                     \
  static const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::SimulationBase, \
                                      DUTIL::ProjectWare>                          \
      factory;

#define D_DEFINE_SIMULATION(REGISTERED_CLASS)                                                   \
  const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::SimulationBase, DUTIL::ProjectWare> \
      REGISTERED_CLASS::factory;

#endif  // DUTIL_SIMULATIONBASE_H
