set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")

find_package(protobuf CONFIG REQUIRED)

set(cpyTa_HEADERS
    protobuf/cpp/stock_info.pb.h
    protobuf/cpp/stock_map.pb.h
    stockanalyzer.h
    stockinfofacade.h
    stockmapfacade.h
)

set(cpyTa_SOURCES
    protobuf/cpp/stock_info.pb.cc
    protobuf/cpp/stock_map.pb.cc
    stockanalyzer.cpp
    stockinfofacade.cpp
    stockmapfacade.cpp
)

add_library(cpyTa)
target_sources(cpyTa PRIVATE
    ${cpyTa_HEADERS}
    ${cpyTa_SOURCES}
)

target_include_directories(cpyTa
    PRIVATE
    .
    ..
    cpp
)
target_link_libraries(cpyTa
    PRIVATE
    dpython
    dutil
    protobuf::protobuf
)


#add_custom_target(my_custom_target
#    DEPENDS
#    "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.pb.h"
#    "${CMAKE_CURRENT_SOURCE_DIR}/python/mail_services/mailservices/protobuf/maildictionary_pb2.py"
#)


#add_custom_command(
#    OUTPUT
#        "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.pb.h"
#    COMMENT
#        "cpyta - compiling mailsettings.proto into C++"
#    COMMAND
#        ${Protobuf_PROTOC_EXECUTABLE} --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/protobuf ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.proto --proto_path ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/
#)

#add_custom_command(
#    OUTPUT
#        "${CMAKE_CURRENT_SOURCE_DIR}/python/mail_services/mailservices/protobuf/mailsettings_pb2.py"
#    COMMENT
#        "cpymail - compiling mailsettings.proto into Python"
#    COMMAND
#        ${Protobuf_PROTOC_EXECUTABLE} --python_out=${CMAKE_CURRENT_SOURCE_DIR}/python/mail_services/mailservices/protobuf/ ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.proto --proto_path ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/
#)

#add_dependencies(cpyta my_custom_target)




