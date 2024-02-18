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
  //! Id of Event this process is waiting for.
  D_NAMED_PARAMETER(TargetId, Event::Id)

  //! Return the validator for construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  /*! \brief Return a default ConsturctionData object.
   *
   * Get a ConstructionData object suitable to build just stand-alone Process-derived
   * objects with no furhter special specifications.
   * This serves mainly as a helper for test purposes.
   */
  static DUTIL::ConstructionData const& getDefaultConstructionData();

  static void init(SimulationBase& sim, DUTIL::ConstructionData const& process_cd);

  //! Resume execution ot hte given process with the value of event.
  static void resume(SimulationBase& sim, Process& process);

  //! Construct with construction data
  explicit Process(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  //! Return the current target process, this porcess depends on, see Process::TargetId.
  Event& getTarget(SimulationBase& sim) const;

  //! Step into the concrete process and call its update method.
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
