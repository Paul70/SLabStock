#include "event.h"

using namespace DUTIL;
using namespace SLABSTOCK;

Event::Event(DUTIL::ConstructionData const &, LoggingSinkPointer sink) :
    LoggingSource(sink)
{}
