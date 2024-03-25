#ifndef SLABSTOCK_CALLBACK_H
#define SLABSTOCK_CALLBACK_H
#include "libd/libdutil/projectware.h"

namespace DUTIL {
class ConstructionValidator;
}

namespace SLABSTOCK {
class Event;
class SimulationBase;

/*! \brief Event Callback base class
 *
 * Base class for all simulation callback typs. Essential purpose is to
 * offer a pure virtual call operator and a factory interface.
 */

class Callback : public DUTIL::ProjectWare
{
  public:
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  void operator()(SimulationBase& sim, Event& event) const;

  private:
  virtual void callbackImpl(SimulationBase& sim, Event& event) const = 0;
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
