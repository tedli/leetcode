cc_library(
    name = "list-node",
    srcs = ["list-node.cc"],
    hdrs = ["list-node.h"],
)

cc_binary(
    name = "main",
    srcs = glob(
        ["*.cc"],
        exclude = ["list-node.cc"],
    ),
    deps = [
        ":list-node",
        "@catch2",
    ],
    copts = ["/std:c++17"],  # MSVC C++17
)
