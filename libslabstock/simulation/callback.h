#ifndef SLABSTOCK_CALLBACK_H
#define SLABSTOCK_CALLBACK_H

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of Callback
 *
 * Longer description of Callback.
 */

class Callback
{
public:
    //! Construct with construction data
    explicit Callback(DUTIL::ConstructionData const & cd);

private:
};

} // namespace SLABSTOCK
#endif // SLABSTOCK_CALLBACK_H
