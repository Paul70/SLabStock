message(STATUS "SLabStock CMakeLists.txt: configuring top level directory")
message(STATUS "Cmake version ${CMAKE_VERSION}")

cmake_minimum_required(VERSION 3.13)

if(NOT PROJECT_NAME)
    project(SLabStock
            VERSION 0.1.0
            DESCRIPTION "Simulation laboratory for stock evaluation and prediction"
            LANGUAGES C CXX
    )
endif()

message(STATUS "SLabStock CMakeLists.txt: loading CMake modules from: ${CMAKE_SOURCE_DIR}/CMakeModules")
list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/CMakeModules
    ${CMAKE_SOURCE_DIR}/libd/CMakeModules)
include(SLabStockVariables)
include(SLabStockDefaultConfig)
include(SLabStockConfigureBuildPaths)

###########################################################
# Manually include libd cmake modules
# Intermediate solution until there is a libd conan package
# aktuell werden die ganzen settings von libd verwendet, das muss dann auch noch umgestellt werden.
message(STATUS "SLabStock CMakeLists.txt: loading CMake modules from: ${CMAKE_SOURCE_DIR}/libd/CMakeModules")
include(${CMAKE_SOURCE_DIR}/libd/CMakeModules/LibdConfig.cmake)
include(${CMAKE_SOURCE_DIR}/libd/CMakeModules/LibdToolchainConfig.cmake)

message(STATUS "SLabStock CMakeLists.txt: configuring subdirectory ${S_LIBD}")
add_subdirectory(libd)
add_subdirectory(libslabstock)
add_subdirectory(libcpymail)
add_subdirectory(cpyTa)

if(O_BUILD_SLABSTOCK_TESTS)
    add_subdirectory(tests)
endif()

