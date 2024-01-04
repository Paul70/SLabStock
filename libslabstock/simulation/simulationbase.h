#ifndef DUTIL_SIMULATIONBASE_H
#define DUTIL_SIMULATIONBASE_H
#include "event.h"
#include "libd/libdutil/namedreference.h"
#include "libd/libdutil/projectware.h"
#include "utility/basictypes.h"

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

  //! Define a simulation id to identify the a concrete simulation object.
  D_NAMED_STRING(Id);

  //! Set of simulation events.
  D_NAMED_REFERENCE(EventList, Event)

  //! Return construction requirements.
  static const DUTIL::ConstructionValidator getConstructionValidator();

  //! Constructor.
  explicit SimulationBase(DUTIL::ConstructionData const& cd,
                          DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  template <typename ConcreteEvent>
  Event::Id createEvent(DUTIL::ConstructionData const& /*cd*/)
  {
    // hier muss ich ein event dynamisch bauen
  }

  // get event das ist ein template

  private:
  Id id_;
  EventMap eventMap_;
  Queue eventQueue_;
  TimeTick now_;
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
