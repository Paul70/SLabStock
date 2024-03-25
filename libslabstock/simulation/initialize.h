#ifndef SLABSTOCK_INITIALIZE_H
#define SLABSTOCK_INITIALIZE_H
#include "event.h"
#include "process.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {

/*! \brief An event for initializing and triggering
 *         a concrete process.
 *
 * Takes as a construction parameter the ConstructionData of the concrete process to start.
 * An Initialize event is always created and scheduled into a simulation each time a
 * concrete process gets initialized, see Process::init() fucntion.
 *
 * An Initialize event also gets as construction parameter a ProcessInitializeCallback.
 * The initializatin logic of a concrete process is:
 * - create an Initializ event for this process
 * - give the Initialize event a ProcessInitializeCallback
 * - schedule the Initialize event in the simulation event queue
 * - when the initialize event gets processed the process initialize callback is called
 * - this callback calls Process::resume() fucntion which runs the concrete processes' update fucntion
 *   for the first time, so update has to be implemented starting with the init state of a process.
 */

class Initialize : public Event, public D_NAMED_CLASS(::SLABSTOCK::Initialize)
{
  public:
  D_DECLARE_EVENT(Initialize)

  D_NAMED_REFERENCE(ProcessToStart, Process)

  static DUTIL::ConstructionValidator const& getConstructionValidator();

  static DUTIL::ConstructionData getProcessCD(Event const& event);

  //! Construct with construction data
  explicit Initialize(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  private:
  virtual std::string whatAmIImpl() const override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_INITIALIZE_H
