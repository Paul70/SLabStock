set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")

find_package(protobuf CONFIG REQUIRED)

set(cpymail_HEADERS
    address.h
    attachment.h
    imailagent.h
    mail.h
    mailagent.h
    protobuf/mailsettings.pb.h
)

set(cpymail_SOURCES
    address.cpp
    attachment.cpp
    mail.cpp
    mailagent.cpp
    protobuf/mailsettings.pb.cc
)

add_library(cpymail)
target_sources(cpymail PRIVATE
    ${cpymail_HEADERS}
    ${cpymail_SOURCES}
)

target_include_directories(cpymail
    PRIVATE
    .
    ..
)
target_link_libraries(cpymail
    PRIVATE
    dpython
    dutil
    protobuf::protobuf
)


add_custom_target(my_custom_target
    DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.pb.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/python/mail_services/mailservices/protobuf/maildictionary_pb2.py"
)


add_custom_command(
    OUTPUT
        "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.pb.h"
    COMMENT
        "cpymail - compiling mailsettings.proto into C++"
    COMMAND
        ${Protobuf_PROTOC_EXECUTABLE} --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/protobuf ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.proto --proto_path ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/
)

add_custom_command(
    OUTPUT
        "${CMAKE_CURRENT_SOURCE_DIR}/python/mail_services/mailservices/protobuf/mailsettings_pb2.py"
    COMMENT
        "cpymail - compiling mailsettings.proto into Python"
    COMMAND
        ${Protobuf_PROTOC_EXECUTABLE} --python_out=${CMAKE_CURRENT_SOURCE_DIR}/python/mail_services/mailservices/protobuf/ ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/mailsettings.proto --proto_path ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/
)

add_dependencies(cpymail my_custom_target)




