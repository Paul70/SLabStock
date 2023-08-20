#ifndef SLABSTOCK_SAF_H
#define SLABSTOCK_SAF_H
#include "libd/libdutil/namedenum.h"
#include <cstdint>

namespace SLABSTOCK {

/*! \brief Type defining the basic time measurement unit.
 *
 * The time progress is counted in values of that type. A std::uint64_t allows
 * long runtime counts and is easy to compare.
 */
using TimeTick = std::uint64_t;

/*! \brief Priority type.
 *
 * Sets a priority for events. This is especially important if two events are scheduled at the same time,
 * e.g. when they have the same scheduled starting time.
 */
D_NAMED_ENUM(Priority, uint64_t, URGENT, NORMAL, LAZY)

} // namespace SLABSTOCK
#endif // SLABSTOCK_SAF_H
