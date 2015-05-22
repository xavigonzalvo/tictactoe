# Agent functionality.

SET(args PROTOFILES agent_model.proto OUTPATH ${CMAKE_CURRENT_SOURCE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${args})
set_source_files_properties(PROTO_SRCS PROTO_HDRS PROPERTIES
                            GENERATED TRUE)

add_library(agents STATIC agent_factory.cc base_agent.cc human_agent.cc
  qlearning_agent.cc random_agent.cc sarsa_agent.cc
  ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(agents config)
target_link_libraries(agents core)
