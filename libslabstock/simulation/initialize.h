#ifndef SLABSTOCK_INITIALIZE_H
#define SLABSTOCK_INITIALIZE_H
#include "event.h"
#include "libd/libdutil/namedclass.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of Initialize
 *
 * Longer description of Initialize.
 */

class Initialize : public Event, public D_NAMED_CLASS(::SLABSTOCK::Initialize)
{
  public:
  //! Construct with construction data
  explicit Initialize(DUTIL::ConstructionData const & cd);

  private:
};

} // namespace SLABSTOCK
#endif // SLABSTOCK_INITIALIZE_H
