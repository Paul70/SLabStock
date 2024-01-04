# Put all runtime, library and archive output artifacts in the same binary folder.
# This is especially helpful for Windows based builds.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "SLabStockConfigureBuildPaths.cmake: runtime binaries are put in:  ${CMAKE_BINARY_DIR}/bin")
message(STATUS "SLabStockConfigureBuildPaths.cmake: library binaries are put in:  ${CMAKE_BINARY_DIR}/bin")
message(STATUS "SLabStockConfigureBuildPaths.cmake: artefact binaries are put in: ${CMAKE_BINARY_DIR}/bin")
