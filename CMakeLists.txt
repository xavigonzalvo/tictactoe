cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("ttt")

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR};../")
include(FindProtobuf)

find_package(ProtocolBuffer REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


SET(args PROTOFILES config.proto OUTPATH ${CMAKE_CURRENT_SOURCE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${args})
set_source_files_properties(PROTO_SRCS PROTO_HDRS PROPERTIES
                            GENERATED TRUE)
add_library(config STATIC ${PROTO_SRCS} ${PROTO_HDRS})

set(gflags_SHARED    FALSE)
set(gflags_NOTHREADS TRUE)
find_package(gflags REQUIRED)

add_subdirectory(core)
add_subdirectory(environment)
add_subdirectory(agents)

add_executable(learner learner_main.cc)

target_link_libraries(learner ${PROTOBUF_LIBRARIES} agents environment gflags)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
