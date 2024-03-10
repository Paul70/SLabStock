#include "simulationsignaler.h"

using namespace DUTIL;
using namespace SLABSTOCK;

SimulationSignaler::SimulationSignaler() :
    timer_(new QTimer(this))
{
  timer_->setTimerType(Qt::PreciseTimer);
  timer_->setSingleShot(true);
  connect(timer_, &QTimer::timeout, this, &SimulationSignaler::stepAndRepeat);
}

void SimulationSignaler::startSimulation()
{
  startSimulationImpl();
}

void SimulationSignaler::stopSimulation()
{
  stopSimulationImpl();
}

void SimulationSignaler::finishSimulation()
{
  timer_->stop();
  emit finishing();
}

void SimulationSignaler::stepAndRepeat()
{
  stepAndDelayImpl(true);
}

void SimulationSignaler::setTimer(int delay_ms)
{
  timer_->start(delay_ms);
}

void SimulationSignaler::update(SimulationState newState)
{
  emit updating(newState.toString());
}
