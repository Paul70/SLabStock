#include "libd/libdutil/clock.h"
#include "libslabstock/simulation/processinitializecallback.h"
#include "tests/testbase.h"

#include "libslabstock/simulation/initialize.h"
#include "libslabstock/simulation/process.h"
#include "libslabstock/simulation/realtimesimulation.h"
#include "libslabstock/simulation/timeout.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/streamloggingsink.h"
#include "libd/libdutil/time.h"

#include <chrono>
#include <sstream>

#include <QCoreApplication>
#include <QTimer>

using namespace SLABSTOCK;
using namespace DUTIL;

namespace {
class SimPyExampleRealTimeCarTests2 : public TestBase
{};

class ExampleRealTimeCar : public Process, public D_NAMED_CLASS(::ExampleRealTimeCar)
{
  public:
  D_DECLARE_PROCESS(ExampleRealTimeCar);

  D_NAMED_ENUM(DrivingState, PARKING, DRIVING);
  static constexpr label_t parkingDuration = 5;  // parking duration in seconds
  static constexpr label_t tripDuration = 2;     // dirving duration in seconds

  //! Inherit constructor.
  using Process::Process;

  Event::Id parking(SimulationBase& sim)
  {
    info("Start parking at " + Utility::toString(sim.now()));
    return Timeout::newInstance(sim, "delay until parking ends", parkingDuration);
  }

  Event::Id driving(SimulationBase& sim)
  {
    info("Start driving at " + Utility::toString(sim.now()));
    return Timeout::newInstance(sim, "delay until driving ends", tripDuration);
  }

  private:
  virtual std::string whatAmIImpl() const override { return getClassName(); }

  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTargetEvent) override
  {
    auto currentValue = getValue();
    if (currentValue.s.getEnum<DrivingState>() == DrivingState::DRIVING) {
      currentValue.setEnum(DrivingState::PARKING);
      newTargetEvent = parking(sim);
    } else {
      currentValue.setEnum(DrivingState::DRIVING);
      newTargetEvent = driving(sim);
    }
    setValue(currentValue);
    return false;
  }
};

D_DEFINE_PROCESS(ExampleRealTimeCar);
}  // namespace

TEST_F(SimPyExampleRealTimeCarTests2, exampleCar1_realTimeInTwoTenthsSeconds_worksAsExpected)
{
  using CD = ConstructionData;

  constexpr auto simTime{15};
  constexpr auto tolerance_s{0.1};
  constexpr auto resolution{0.2};
  constexpr auto puffer{50};

  int dummyArgc = 0;
  QCoreApplication app(dummyArgc, nullptr);

  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);

  // clang-format off
  RealTimeSimulation simRT(
      ConstructionData()
          .setParameter<RealTimeSimulation::Tolerance_s>(tolerance_s)
          .addSubobject<RealTimeSimulation::RealTime>(
              CD().setEnum(Clock::Type::STEADY)
                  .setConcreteClassParameter<Clock>())
          .addSubobject<SimulationBase::EventTicker>(
              CD().setParameter<Ticker::Resolution_s>(resolution)
                  .setConcreteClassParameter<Ticker>()),
      sls);
  // clang-format on

  Process::init(simRT, ConstructionData{}
                           .setConcreteClassParameter<ExampleRealTimeCar>()
                           .setEnum(ExampleRealTimeCar::DrivingState::DRIVING)
                           .setParameter<Process::Description>("Example 1 car real time"));

  // timer to start simulation event processing
  QTimer::singleShot(0, &simRT, [&]() { simRT.runUntil(simTime); });
  QObject::connect(&simRT, &RealTimeSimulation::finishing, &app, &QCoreApplication::quit);

  // start QApplication
  auto start = std::chrono::steady_clock::now();
  app.exec();
  auto end = std::chrono::steady_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  auto result = duration - (simTime * TIME::oneByMilli * resolution + puffer);

  // Single puffer of 50 ms is per event and we allow an absolut puffer of 4 times a single puffer
  // which is 4*50 ms = 200 ms
  // Exact result is -50 ms.
  EXPECT_LE(result, 200);

  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 7"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 12"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 14"));
}

TEST_F(SimPyExampleRealTimeCarTests2, exampleCar1_realTimeInOneTenthsOfASecond_worksAsExpected)
{
  using CD = ConstructionData;

  constexpr auto simTime{15};
  constexpr auto tolerance_s{0.1};
  constexpr auto resolution{0.1};
  constexpr auto puffer{50};

  int dummyArgc = 0;
  QCoreApplication app(dummyArgc, nullptr);

  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);

  // clang-format off
  RealTimeSimulation simRT(
      ConstructionData()
          .setParameter<RealTimeSimulation::Tolerance_s>(tolerance_s)
          .addSubobject<RealTimeSimulation::RealTime>(
              CD().setEnum(Clock::Type::STEADY)
                  .setConcreteClassParameter<Clock>())
          .addSubobject<SimulationBase::EventTicker>(
              CD().setParameter<Ticker::Resolution_s>(resolution)
                  .setConcreteClassParameter<Ticker>()),
      sls);
  // clang-format on

  Process::init(simRT, ConstructionData{}
                           .setConcreteClassParameter<ExampleRealTimeCar>()
                           .setEnum(ExampleRealTimeCar::DrivingState::DRIVING)
                           .setParameter<Process::Description>("Example 1 car real time"));

  // timer to start simulation event processing
  QTimer::singleShot(0, &simRT, [&]() { simRT.runUntil(simTime); });
  QObject::connect(&simRT, &RealTimeSimulation::finishing, &app, &QCoreApplication::quit);

  // start QApplication
  auto start = std::chrono::steady_clock::now();
  app.exec();
  auto end = std::chrono::steady_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  auto result = duration - (simTime * TIME::oneByMilli * resolution + puffer);

  // Single puffer of 50 ms is per event and we allow an absolut puffer of 4 times a single puffer
  // which is 4*50 ms = 200 ms
  // Exact result is -50 ms.
  EXPECT_LE(result, 200);

  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 7"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 12"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 14"));
}

TEST_F(SimPyExampleRealTimeCarTests2, exampleCar1_realTimeInOneHundredsOfASecond_worksAsExpected)
{
  using CD = ConstructionData;

  constexpr auto simTime{15};
  constexpr auto tolerance_s{0.1};
  constexpr auto resolution{0.01};
  constexpr auto puffer{50};

  int dummyArgc = 0;
  QCoreApplication app(dummyArgc, nullptr);

  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);

  // clang-format off
  RealTimeSimulation simRT(
      ConstructionData()
          .setParameter<RealTimeSimulation::Tolerance_s>(tolerance_s)
          .addSubobject<RealTimeSimulation::RealTime>(
              CD().setEnum(Clock::Type::STEADY)
                  .setConcreteClassParameter<Clock>())
          .addSubobject<SimulationBase::EventTicker>(
              CD().setParameter<Ticker::Resolution_s>(resolution)
                  .setConcreteClassParameter<Ticker>()),
      sls);
  // clang-format on

  Process::init(simRT, ConstructionData{}
                           .setConcreteClassParameter<ExampleRealTimeCar>()
                           .setEnum(ExampleRealTimeCar::DrivingState::DRIVING)
                           .setParameter<Process::Description>("Example 1 car real time"));

  // timer to start simulation event processing
  QTimer::singleShot(0, &simRT, [&]() { simRT.runUntil(simTime); });
  QObject::connect(&simRT, &RealTimeSimulation::finishing, &app, &QCoreApplication::quit);

  // start QApplication
  auto start = std::chrono::steady_clock::now();
  app.exec();
  auto end = std::chrono::steady_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  auto result = duration - (simTime * TIME::oneByMilli * resolution + puffer);

  // Single puffer of 50 ms is per event and we allow an absolut puffer of 4 times a single puffer
  // which is 4*50 ms = 200 ms
  // Exact result is -50 ms.
  EXPECT_LE(result, 200);

  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 7"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 12"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 14"));
}

TEST_F(SimPyExampleRealTimeCarTests2,
       exampleCar1_SetupWithConstructionDataRealTimeInOneTenthsOfASecond_worksAsExpected)
{
  using CD = ConstructionData;

  constexpr auto simTime{15};
  constexpr auto tolerance_s{0.1};
  constexpr auto resolution{0.1};
  constexpr auto puffer{50};

  int dummyArgc = 0;
  QCoreApplication app(dummyArgc, nullptr);

  auto oss = std::make_shared<std::stringstream>();
  auto sls = std::make_shared<StreamLoggingSink>(oss, LoggingSink::LogSeverity::INFO);

  // clang-format off
  RealTimeSimulation simRT(
      ConstructionData()
          // SimulationBase construction data:
          // Dataset for init event id, priority and tick, see SimulationBase constructor implementation.
          .set(Dataset(std::vector<DUTIL::Ticker::Tick>{0, 0, 0}, 3))
          .addSubobject<SimulationBase::EventList>(
            CD().setConcreteClassParameter<Initialize>()
                .setParameter<Initialize::IdParam>(0)
                .setParameter<Initialize::Description>("Init event for concrete process ExampleCar1 real time.")
                .addSubobject<Initialize::CallbackList>(
                  CD().setConcreteClassParameter<ProcessInitializeCallback>())
                .addSubobject<Initialize::ProcessToStart>(
                  CD().setConcreteClassParameter<ExampleRealTimeCar>()
                      .setParameter<Event::IdParam>(1)
                      .setParameter<Process::TargetId>(0)
                      .setEnum(ExampleRealTimeCar::DrivingState::DRIVING)
                      .setParameter<Process::Description>("ExampleCar1 real time"))
          )
          // RealTimeSimulation construction data:
          .setParameter<RealTimeSimulation::Tolerance_s>(tolerance_s)
          .addSubobject<RealTimeSimulation::RealTime>(
              CD().setEnum(Clock::Type::STEADY)
                  .setConcreteClassParameter<Clock>())
          .addSubobject<SimulationBase::EventTicker>(
              CD().setParameter<Ticker::Resolution_s>(resolution)
                  .setConcreteClassParameter<Ticker>()),
      sls);
  // clang-format on

  // timer to start simulation event processing
  QTimer::singleShot(0, &simRT, [&]() { simRT.runUntil(simTime); });
  QObject::connect(&simRT, &RealTimeSimulation::finishing, &app, &QCoreApplication::quit);

  // start QApplication
  auto start = std::chrono::steady_clock::now();
  app.exec();
  auto end = std::chrono::steady_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  auto result = duration - (simTime * TIME::oneByMilli * resolution + puffer);

  // Single puffer of 50 ms is per event and we allow an absolut puffer of 4 times a single puffer
  // which is 4*50 ms = 200 ms
  // Exact result is -50 ms.
  EXPECT_LE(result, 200);

  auto const os = oss->str();
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 0"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 5"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 7"));
  EXPECT_THAT(os, testing::HasSubstr("Start driving at 12"));
  EXPECT_THAT(os, testing::HasSubstr("Start parking at 14"));
}
