message(STATUS "SLabStock CMakeLists.txt: configuring subdirectory ${S_TESTS}")

set(libd_tests_HEADERS
    testbase.h
)
set(slabstock_tests_SOURCES
    libslabstock/simulationtests.cpp
    main.cpp
    simpy_examples/simpyexample_car.cpp
    simpy_examples/simpyexample_realtimecar.cpp
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
