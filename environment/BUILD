# Description:
#   Environment library. Ideally this could also be a generic class so
#   that the reinforcement learning system is completely
#   generic. Since this is an exercie I've opted to leave the
#   environment fixed for the task at hand (ie. Tic-Tac-Toe).

package(
    default_visibility = ["//visibility:public"],
    features = ["no_layering_check"],
)

cc_library(
    name = "states",
    srcs = ["tictactoe_state.cc"],
    hdrs = [
        "state.h",
        "state_handler.h",
        "tictactoe_state.h",
    ],
    deps = [
        "//base",
        "//strings",
    ],
)

cc_library(
    name = "environment",
    srcs = ["tictactoe_environment.cc"],
    hdrs = [
        "environment.h",
        "tictactoe_environment.h",
    ],
    deps = [
        ":states",
        "//experimental/users/xavigonzalvo/ttt/agents",
    ],
)

cc_library(
    name = "actions",
    srcs = ["actions.cc"],
    hdrs = [
        "actions.h",
        "tictactoe_actions.h",
    ],
    deps = [
        ":states",
        "//util/random:random_no_openssl",
    ],
)

cc_test(
    name = "tictactoe_state_test",
    srcs = ["tictactoe_state_test.cc"],
    deps = [
        ":states",
        "//testing/base/public:gunit_main",
    ],
)
