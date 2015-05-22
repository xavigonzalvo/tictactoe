add_library(environment STATIC actions.cc tictactoe_environment.cc tictactoe_state.cc)

target_link_libraries(environment core)