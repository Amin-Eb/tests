proto_library(
    name = "addressbook_proto",
    srcs = ["addressbook.proto"],
)

cc_proto_library(
    name = "addressbook_cc_proto",
    deps = [":addressbook_proto"],
)

cc_binary(
    name = "proto_sample",
    srcs = ["main.cpp"],
    deps = [":addressbook_cc_proto"],
)

