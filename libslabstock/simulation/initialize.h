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

/*! \brief description of Initialize
 *
 * Longer description of Initialize.
 */

class Initialize : public Event, public D_NAMED_CLASS(::SLABSTOCK::Initialize)
{
  public:
  D_DECLARE_EVENT(Initialize)

  D_NAMED_REFERENCE(ProcessToStart, Process)

  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Construct with construction data
  explicit Initialize(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  private:
  virtual std::string whatAmIImpl() const override;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_INITIALIZE_H
