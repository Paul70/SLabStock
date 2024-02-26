message(STATUS "libslabstock CMakeLists.txt: configuring subdirectory ${S_LIB_SLABSTOCK}")

find_package(ZLIB REQUIRED)
#find_package()

set(slabstock_HEADERS
    simulation/callback.h
    simulation/clearsimulationcallback.h
    simulation/dummyprocess.h
    simulation/event.h
    simulation/finalize.h
    simulation/initialize.h
    simulation/process.h
    simulation/processfinalizecallback.h
    simulation/processinitializecallback.h
    simulation/processresumecallback.h
    simulation/realtimesimulation.h
    simulation/simulation.h
    simulation/simulationbase.h
    simulation/simulationsignaler.h
    simulation/timeout.h
    utility/basictypes.h
)
set(slabstock_SOURCES
    simulation/callback.cpp
    simulation/clearsimulationcallback.cpp
    simulation/dummyprocess.cpp
    simulation/event.cpp
    simulation/finalize.cpp
    simulation/initialize.cpp
    simulation/process.cpp
    simulation/processfinalizecallback.cpp
    simulation/processinitializecallback.cpp
    simulation/processresumecallback.cpp
    simulation/realtimesimulation.cpp
    simulation/simulation.cpp
    simulation/simulationbase.cpp
    simulation/simulationsignaler.cpp
    simulation/timeout.cpp
)

add_library(slabstock)
target_sources(slabstock PRIVATE
    ${slabstock_HEADERS}
    ${slabstock_SOURCES}
)
target_include_directories(slabstock PRIVATE
    .
    ..
)
target_link_libraries(slabstock PUBLIC
    dglobals
    dutil
    ZLIB::ZLIB
)

