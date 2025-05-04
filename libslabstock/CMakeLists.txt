message(STATUS "libslabstock CMakeLists.txt: configuring subdirectory ${S_LIB_SLABSTOCK}")

#find_package(pybind11 CONFIG REQUIRED)
find_package(mariadb-connector-c CONFIG REQUIRED)
find_package(ZLIB CONFIG REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS
    Core
)
find_package(protobuf CONFIG REQUIRED)

set(slabstock_HEADERS
    application/stockcrawler.h
    database/connector.h
    database/databaseaccessbuilder.h
    database/sqlclient.h
    database/idatabaseaccess.h
    database/isinmapping.h
    database/sqlcommand.h
    database/sqldriverfactory.h
    database/sqltable.h
    database/sqldatabase.h
    database/sqldatabaseaccess.h
    database/types.h
    simulation/callback.h
    simulation/clearsimulationcallback.h
    simulation/dummyprocess.h
    simulation/event.h
    simulation/finalize.h
    simulation/initialize.h
    simulation/interrupt.h
    simulation/process.h
    simulation/processfinalizecallback.h
    simulation/processinitializecallback.h
    simulation/processinterruptcallback.h
    simulation/processresumecallback.h
    simulation/realtimesimulation.h
    simulation/simulation.h
    simulation/simulationbase.h
    simulation/simulationsignaler.h
    simulation/timeout.h
    utility/basictypes.h
)
set(slabstock_SOURCES
    application/stockcrawler.cpp
    database/connector.cpp
    database/sqlclient.cpp
    database/idatabaseaccess.cpp
    database/isinmapping.cpp
    database/sqlcommand.cpp
    database/sqltable.cpp
    database/sqldatabase.cpp
    database/sqldatabaseaccess.cpp
    simulation/callback.cpp
    simulation/clearsimulationcallback.cpp
    simulation/dummyprocess.cpp
    simulation/event.cpp
    simulation/finalize.cpp
    simulation/initialize.cpp
    simulation/interrupt.cpp
    simulation/process.cpp
    simulation/processfinalizecallback.cpp
    simulation/processinitializecallback.cpp
    simulation/processinterruptcallback.cpp
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
target_include_directories(slabstock
    PRIVATE
    .
    ..
)
target_link_libraries(slabstock
    PUBLIC
    protobuf::protobuf
    dglobals
    dpython
    dutil
    mariadb-connector-c::mariadb-connector-c
    mariadbcpp
    ZLIB::ZLIB
    Qt5::Core
    #pybind11_all_do_not_use
    cpymail
    cpyTa
)
set_target_properties(slabstock PROPERTIES
    DEFINE_SYMBOL ""
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)

