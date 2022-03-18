cc_library(
    name = "core",
    srcs = [
        "CPod.cpp",
        "CStateMachine.cpp",
    ],
    hdrs = [
        "CPod.hpp",
        "CStateMachine.hpp",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "CStateMachine_test",
    srcs = ["CStatemachine_test.cpp"],
    deps = [
        ":core",
        "@com_google_googletest//:gtest_main",
    ],
)
