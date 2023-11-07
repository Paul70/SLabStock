#ifndef SLABSTOCK_SIMULATION_H
#define SLABSTOCK_SIMULATION_H
#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "simulationbase.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <zlib.h>



namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of Simulation
 *
 * Longer description of Simulation.
 */

class Simulation : public SimulationBase, public D_NAMED_CLASS(::SLABSTOCK::Simulation)
{
public:
    //! Declare static factory member
    D_DECLARE_PROJECTWARE(Simulation)

    void doSomethingWithZlib() const
    {
        //constexpr auto range = semver::range(">=1.0.0 <2.0.0 || >3.2.1");
        char buffer_in [256] = {"Conan is a MIT-licensed, Open Source package manager for C and C++ development "
                               "for C and C++ development, allowing development teams to easily and efficiently "
                               "manage their packages and dependencies across platforms and build systems."};
        char buffer_out [256] = {0};

        z_stream defstream;
        defstream.zalloc = Z_NULL;
        defstream.zfree = Z_NULL;
        defstream.opaque = Z_NULL;
        defstream.avail_in = (uInt) strlen(buffer_in);
        defstream.next_in = (Bytef *) buffer_in;
        defstream.avail_out = (uInt) sizeof(buffer_out);
        defstream.next_out = (Bytef *) buffer_out;

        deflateInit(&defstream, Z_BEST_COMPRESSION);
        deflate(&defstream, Z_FINISH);
        deflateEnd(&defstream);

        printf("Uncompressed size is: %lu\n", strlen(buffer_in));
        printf("Compressed size is: %lu\n", strlen(buffer_out));

        printf("ZLIB VERSION: %s\n", zlibVersion());
    }

    //! Construct with construction data
    explicit Simulation(DUTIL::ConstructionData const &cd, DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

private:
};

} // namespace SLABSTOCK
#endif // SLABSTOCK_SIMULATION_H
