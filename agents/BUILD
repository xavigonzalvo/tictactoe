# Description:
#   Agent libraries. Each agent is registered and accessed using its
#   name in the main tool.

package(
    default_visibility = ["//visibility:public"],
    features = ["no_layering_check"],
)

proto_library(
    name = "agent_model_proto",
    srcs = ["agent_model.proto"],
    cc_api_version = 2,
    py_api_version = 2,
)

cc_library(
    name = "agents",
    srcs = [
        "base_agent.cc",
        "human_agent.cc",
        "qlearning_agent.cc",
        "random_agent.cc",
        "sarsa_agent.cc",
    ],
    hdrs = [
        "base_agent.h",
        "human_agent.h",
        "qlearning_agent.h",
        "random_agent.h",
        "sarsa_agent.h",
    ],
    deps = [
        ":agent_model_proto",
        "//experimental/users/xavigonzalvo/ttt:config",
        "//experimental/users/xavigonzalvo/ttt/environment:actions",
        "//experimental/users/xavigonzalvo/ttt/environment:states",
        "//file/base",
        "//util/gtl:map_util",
        "//util/random:random_no_openssl",
        "//util/registration",
    ],
    alwayslink = 1,  # Registered classes
)
