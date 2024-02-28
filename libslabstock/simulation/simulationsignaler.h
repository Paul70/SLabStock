#ifndef SLABSTOCK_SIMULATIONSIGNALER_H
#define SLABSTOCK_SIMULATIONSIGNALER_H
#include <QObject>
#include <QTimer>

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK {

/*! \brief description of SimulationSignaler
 *
 * Longer description of SimulationSignaler.
 */

class SimulationSignaler : public QObject
{
  Q_OBJECT

  public:
  //! Construct with construction data
  explicit SimulationSignaler(DUTIL::ConstructionData const& cd);

  private:
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_SIMULATIONSIGNALER_H
