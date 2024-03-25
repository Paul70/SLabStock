message(STATUS "SLabStock CMakeLists.txt: configuring subdirectory ${S_TESTS}")

set(libd_tests_HEADERS
    testbase.h
)
set(slabstock_tests_SOURCES
    libslabstock/simulationtests.cpp
    main.cpp
    simpy_examples/simpyexample1_car.cpp
    simpy_examples/simpyexample2_realtimecar.cpp
    simpy_examples/simpyexample3_chargingcar.cpp
    simpy_examples/simpyexample4_cardriver.cpp
    testbase.cpp
)

find_package(GTest CONFIG REQUIRED)


add_executable(slabstock_tests)
target_sources(slabstock_tests PRIVATE
    ${libd_tests_HEADERS}
    ${slabstock_tests_SOURCES}
)

target_include_directories(slabstock_tests PUBLIC
    .
    ..
)
target_link_libraries(slabstock_tests PUBLIC
    GTest::gtest
    GTest::gmock
    dglobals
    dutil
    slabstock
)
