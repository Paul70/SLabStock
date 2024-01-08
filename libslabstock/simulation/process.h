#ifndef SLABSTOCK_PROCESS_H
#define SLABSTOCK_PROCESS_H
#include "event.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {

class SimulationBase;

/*! \brief description of Process
 *
 * Longer description of Process.
 */

class Process : public Event
{
  public:
  //! Id of Event this process is initially waiting for.
  D_NAMED_PARAMETER(TargetId, Event::Id)

  static DUTIL::ConstructionValidator const& getConstructionValidator();

  static void init(SimulationBase& sim, DUTIL::ConstructionData const& process_cd);

  //! Construct with construction data
  explicit Process(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  bool update(SimulationBase& sim, Event::Id& newTarget);

  private:
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTarget) = 0;
  Event::Id targetId_;
};

}  // namespace SLABSTOCK

D_DECLARE_FACTORYINTERFACE(::SLABSTOCK::Process)

#define D_DECLARE_PROCESS(REGISTERED_CLASS)                                                   \
  static const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Process, SLABSTOCK::Event> \
      factory;

#define D_DEFINE_PROCESS(REGISTERED_CLASS)                                             \
  const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Process, SLABSTOCK::Event> \
      REGISTERED_CLASS::factory;

#endif  // SLABSTOCK_PROCESS_H
