#ifndef SLABSTOCK_EVENT_H
#define SLABSTOCK_EVENT_H
#include "libd/libdutil/loggingsource.h"
#include "libd/libdutil/namedparameter.h"
#include "libd/libdutil/projectware.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of Event
 *
 * Longer description of Event.
 */

class Event : public DUTIL::ProjectWare, public DUTIL::LoggingSource
{
public:
    using Id = std::uint64_t;

    D_NAMED_PARAMETER(IdParam, Id)

    //! Default constructor.
    Event(DUTIL::ConstructionData const &cd, LoggingSinkPointer sink = nullptr);

private:
};

} // namespace SLABSTOCK

D_DECLARE_FACTORYINTERFACE(SLABSTOCK::Event)

#define D_DECLARE_Event(REGISTERED_CLASS) \
    static const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Event, DUTIL::ProjectWare> factory;

#define D_DEFINE_Event(REGISTERED_CLASS) \
    const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Event, DUTIL::ProjectWare> REGISTERED_CLASS::factory;
#endif // SLABSTOCK_EVENT_H
