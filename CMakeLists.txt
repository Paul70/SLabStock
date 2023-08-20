cmake_minimum_required(VERSION 3.13)

if(NOT PROJECT_NAME)
    project(SLabStock
            VERSION 0.1.0
            DESCRIPTION "Simulation laboratory for stock evaluation and prediction"
            LANGUAGES C CXX)
endif()

message(STATUS "Loading CMake modules")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules ${CMAKE_CURRENT_SOURCE_DIR}/libd/CMakeModules)
include(HelperFunctions)
include(LibdDefaultConfig)
include(ConfigureBuildPaths)

# Global options for libd project. Have to be set before loading cmake modules.
option(BUILD_SLABSTOCK_TESTS "Build SLabStock tests and use system installed GoogleTest framework" ON)
option(BUILD_SLABSTOCK_TESTS_AND_GOOGLETEST "Build libd Googletest test suite and Googletest framework itsself" OFF)
option(SLABSTOCK_USE_CTESTS "Use cmake's CTest framework to run all registered unit tests after a successfull build" OFF)
option(USE_CXX_20 "Enable C++ 20 features. Option gets deactivated if the compiler does not support C++ 20." OFF)

# Set libw build options, overwrites options in libw sub-project.
add_subdirectory(libd)

# Internal options depending on LibdDefaultConfig module
option(BUILD_SHARED_LIBS "Build all libraries as shared libs unless it is defined ohterwise" ${D_DEFAULT_BUILD_SHARED_LIBS})

add_subdirectory(libslabstock)

if(BUILD_SLABSTOCK_TESTS)
    set(BUILD_LIBD_TESTS_AND_GOOGLETEST OFF)
    add_subdirectory(tests)
endif()
