#ifndef SLABSTOCK_PROCESS_H
#define SLABSTOCK_PROCESS_H
#include "event.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of Process
 *
 * Longer description of Process.
 */

class Process : public Event
{
public:
    //! Construct with construction data
    using Event::Event;

private:
};

} // namespace SLABSTOCK

D_DECLARE_FACTORYINTERFACE(SLABSTOCK::Process)

#define D_DECLARE_PROCESS(REGISTERED_CLASS) \
    static const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Process, SLABSTOCK::Event> factory;

#define D_DEFINE_PROCESS(REGISTERED_CLASS) \
    const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Process, SLABSTOCK::Event> REGISTERED_CLASS::factory;

#endif // SLABSTOCK_PROCESS_H
