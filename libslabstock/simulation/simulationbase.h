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
} // namespace DUTIL

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

    using QueueKey = std::pair<TimeTick, Priority>;

    using Queue = std::multimap<QueueKey, Event::Id>;

    //! Define a simulation id to be able to identify the simulation object later.
    D_NAMED_STRING(Id);

    D_NAMED_REFERENCE(EventList, Event)

    static const DUTIL::ConstructionValidator getConstructionValidator();

    //! Default constructor.
    explicit SimulationBase(DUTIL::ConstructionData const &cd, DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

    // functions:
    //createEvent

    // get event das ist ein template

    //als naechstes muss ich in libdutil in den Settings eine buildSubobject list anlegen, damit ich events in die cd packen kann

        private : Id id_;
    EventMap eventMap_;
    Queue eventQueue_;
    TimeTick now_;
};
} // namespace SLABSTOCK
#endif // DUTIL_SIMULATIONBASE_H
