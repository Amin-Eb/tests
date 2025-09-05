cc_library(
    name = "nlohmann_json",
    hdrs = ["3rdparty/nlohmann/json.hpp"],
    includes = ["3rdparty"],  # now you can #include "nlohmann/json.hpp"
    visibility = ["//visibility:public"],
)

# ---------- First ----------
proto_library(
    name = "first_proto",
    srcs = ["first.proto"],
)

cc_proto_library(
    name = "first_cc_proto",
    deps = [":first_proto"],
)

cc_binary(
    name = "first_writer",
    srcs = ["first_writer.cpp"],
    deps = [":first_cc_proto", ":nlohmann_json",],
)

# ---------- Second ----------
proto_library(
    name = "second_proto",
    srcs = ["second.proto"],
)

cc_proto_library(
    name = "second_cc_proto",
    deps = [":second_proto"],
)

cc_binary(
    name = "second_writer",
    srcs = ["second_writer.cpp"],
    deps = [":second_cc_proto", ":nlohmann_json",],
)

# ---------- Third ----------
proto_library(
    name = "third_proto",
    srcs = ["third.proto"],
)

cc_proto_library(
    name = "third_cc_proto",
    deps = [":third_proto"],
)

cc_binary(
    name = "third_writer",
    srcs = ["third_writer.cpp"],
    deps = [":third_cc_proto", ":nlohmann_json",],
)

