#ifndef SLABSTOCK_CALLBACK_H
#define SLABSTOCK_CALLBACK_H
#include "libd/libdutil/projectware.h"

namespace DUTIL {
class ConstructionValidator;
}

namespace SLABSTOCK {

/*! \brief description of Callback
 *
 * Longer description of Callback.
 */

class Callback : public DUTIL::ProjectWare
{
  public:
  static DUTIL::ConstructionValidator const& getConstructinValidator();

  private:
};

}  // namespace SLABSTOCK

D_DECLARE_FACTORYINTERFACE(::SLABSTOCK::Callback)

#define D_DECLARE_CALLBACK(REGISTERED_CLASS)                                                     \
  static const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Callback, DUTIL::ProjectWare> \
      factory;

#define D_DEFINE_CALLBACK(REGISTERED_CLASS)                                               \
  const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Callback, DUTIL::ProjectWare> \
      REGISTERED_CLASS::factory;
#endif  // SLABSTOCK_CALLBACK_H
