#include "dummyprocess.h"

using namespace DUTIL;
using namespace SLABSTOCK;

D_DEFINE_PROCESS(DummyProcess)

std::string DummyProcess::whatAmIImpl() const
{
  return this->getConcreteClassName();
}

bool DummyProcess::updateImpl(SimulationBase& /*sim*/, Event::Id& /*newTarget*/)
{
  return true;
}
