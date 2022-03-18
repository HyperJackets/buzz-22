cc_library(
    name = "core",
    srcs = [
        "core/CPod.cpp",
        "core/CStateMachine.cpp",
    ],
    hdrs = [
        "core/CPod.hpp",
        "core/CStateMachine.hpp",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "CStateMachine_test",
    srcs = ["core/CStatemachine_test.cpp"],
    deps = [
        ":core",
        "@com_google_googletest//:gtest_main",
    ],
)
