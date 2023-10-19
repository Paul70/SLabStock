set(slabstock_HEADERS
    simulation/callback.h
    simulation/dummyprocess.h
    simulation/event.h
    simulation/process.h
    simulation/simulation.h
    simulation/simulationbase.h
    thirdparty/semver/include/semver.hpp
    utility/basictypes.h
)
set(slabstock_SOURCES
    simulation/callback.cpp
    simulation/dummyprocess.cpp
    simulation/event.cpp
    simulation/process.cpp
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
)