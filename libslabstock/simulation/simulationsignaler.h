#ifndef SLABSTOCK_SIMULATIONSIGNALER_H
#define SLABSTOCK_SIMULATIONSIGNALER_H
#include "libd/libdutil/namedenum.h"

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
  //! Define possible Simulation states
  D_NAMED_ENUM(SimulationState, STOPPED, RUNNING, PREPARING_TO_RUN, PREPARING_TO_STOP)

  //! Construct instance
  SimulationSignaler();

  public slots:
  //! Run the simulation as long as there are scheduled events.
  void startSimulation();

  /*! \brief Shut down the simulation.
   *
   * Schedules a Finalize event that will clear all scheduled events.
   */
  void stopSimulation();

  //! Perform an immediate halt.
  void finishSimulation();

  private slots:
  void stepAndRepeat();

  signals:
  //! This signal is emitted when the simulation changes its state.
  void updating(std::string newState);

  //! This signal is emitted when the simulation is done and can be deleted.
  void finishing();

  protected:
  void setTimer(int delay_ms);
  void update(SimulationState newState);

  private:
  QTimer* timer_;

  virtual void startSimulationImpl() = 0;
  virtual void stopSimulationImpl() = 0;
  virtual void stepAndDelayImpl(bool doStep) = 0;
};

}  // namespace SLABSTOCK
#endif  // SLABSTOCK_SIMULATIONSIGNALER_H
