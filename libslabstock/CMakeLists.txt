message(STATUS "libslabstock CMakeLists.txt: configuring subdirectory ${S_LIB_SLABSTOCK}")

find_package(ZLIB REQUIRED)

set(slabstock_HEADERS
    simulation/callback.h
    simulation/dummyprocess.h
    simulation/event.h
    simulation/initialize.h
    simulation/process.h
    simulation/processinitializecallback.h
    simulation/simulation.h
    simulation/simulationbase.h
    utility/basictypes.h
)
set(slabstock_SOURCES
    simulation/callback.cpp
    simulation/dummyprocess.cpp
    simulation/event.cpp
    simulation/initialize.cpp
    simulation/process.cpp
    simulation/processinitializecallback.cpp
    simulation/simulation.cpp
    simulation/simulationbase.cpp
)

add_library(slabstock)
target_sources(slabstock PRIVATE
    ${slabstock_HEADERS}
    ${slabstock_SOURCES}
)
target_include_directories(slabstock PRIVATE .. .)
target_link_libraries(slabstock PUBLIC
    dutil
    ZLIB::ZLIB
)

