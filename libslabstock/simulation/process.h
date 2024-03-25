#ifndef SLABSTOCK_PROCESS_H
#define SLABSTOCK_PROCESS_H
#include "event.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {

class SimulationBase;
class Interrupt;

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

  /*! \brief Creates and schedules an initialize event for a concrete Process
   *  and leaves the process on its own, afterwards.
   *
   * This function can be used to create a concrete process directly and put
   * it into a simulation. The benefit is, that the simulation may be already
   * started and we can no longer pass it into a simulatio via construction data.
   * See the simpy examples for use cases.
   *
   * Leaving the process on its own means, that we do not return the event id (which
   * arises during process creation) for further referecning in other processes.
   *
   *
   * \param:
   * sim: Referece to the simulation instance.
   * process_cd: Reference to a construction data object for a concrete process to create and initilize.
   */
  static void init(SimulationBase& sim, DUTIL::ConstructionData const& process_cd);

  /*! \brief Creates and executes a new concrete process and retruns its Id.
   *
   * This method creates a new concrete process and triggers its execution immediatly
   * by addtionally creating a Timeout event which owns a ProcessResumeCallback
   * referring to the newly created process.
   *
   * By returning the Id of the newly created process, it is possible to use
   * this procss as a target of another process. Therefore, the other process is
   * in some sense the parent of this new process since it is a condition for its
   * creation.
   *
   *
   * \param:
   * sim: Referece to the simulation instance.
   * process_cd: Reference to a construction data object for a concrete process to create and initilize.
   */
  [[nodiscard]] static Process::Id initWithParent(SimulationBase& sim,
                                                  DUTIL::ConstructionData process_cd);

  /*! \brief Resume execution of the given process with the value of event.
   *
   * Condition to get into this method is to call a ProcessResumeCallback.
   * Method calls the concrete process' update method to trigger process execution.
   * Method creates a new ProcessResumeCallback inside the target process of this process
   * to trigger executio again.
   *
   * \param:
   * sim: Referece to the simulation instance.
   * process: Reference to the concrete process (not the target process) to resume.
   */
  static void resume(SimulationBase& sim, Process& process);

  /*! \brief Interrupt process execution with the given interruption event.
   *
   * Method is triggerd via a ProcessInterruptCallback. Calls the interrupt() method
   * of the concrete process (or the default one) and lets the process handle the
   * interruption. Creates a ProcessResumeCallback in the target porcess of the
   * interrupted process if needed.
   *
   * \param:
   * sim: Referece to the simulation instance owning the process.
   * process: Reference to the concrete process (not the target process) to be interrupted.
   * interrupt: Reference to the interrupt event.
   */
  static void interrupt(SimulationBase& sim, Process& process, Interrupt& interrupt);

  //! Construct with construction data
  explicit Process(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  //! Return the current target process, this porcess depends on, see Process::TargetId.
  Event& getTarget(SimulationBase& sim) const;

  //! Step into the concrete process and call its update method.
  bool update(SimulationBase& sim, Event::Id& newTarget);

  private:
  //! Placeholder (default implementation) for process resume mechanism.
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTarget) = 0;

  //! Placeholder (default implementation) for process interrupt mechanism.
  virtual bool interruptImpl(SimulationBase&, Interrupt& i, Event::Id&);

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
