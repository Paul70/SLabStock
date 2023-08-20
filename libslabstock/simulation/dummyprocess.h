#ifndef SLABSTOCK_DUMMYPROCESS_H
#define SLABSTOCK_DUMMYPROCESS_H
#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "process.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of DummyProcess
 *
 * Longer description of DummyProcess.
 */

class DummyProcess : public Process, public D_NAMED_CLASS(::SLABSTOCK::DummyProcess)
{
public:
    //! Declare static factory member.
    D_DECLARE_PROCESS(DummyProcess)

    //! Construct with construction data
    using Process::Process;

private:
};

} // namespace SLABSTOCK
#endif // SLABSTOCK_DUMMYPROCESS_H
