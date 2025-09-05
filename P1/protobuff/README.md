# Protobuf Serialization Example

This project demonstrates serializing JSON data to Protobuf binaries for three different data schemes.

## Project Structure

```
protobuff/
├── first.proto
├── second.proto
├── third.proto
├── first_writer.cpp
├── second_writer.cpp
├── third_writer.cpp
├── BUILD
├── MODULE.bazel
├── ../json/first.json
├── ../json/second.json
└── ../json/third.json
```

* `*.proto` — Protobuf schemas for three data structures.
* `*_writer.cpp` — C++ code to read JSON, serialize to Protobuf binary, and save.
* `BUILD` & `MODULE.bazel` — Bazel build configuration.
* `../json/*.json` — Sample JSON input files.

---

## Steps to Build and Run

1. **Compile Protobuf schemas**

```bash
protoc --cpp_out=. first.proto
protoc --cpp_out=. second.proto
protoc --cpp_out=. third.proto
```

This generates `*.pb.h` and `*.pb.cc` files.

---

2. **Write C++ code**

Each `_writer.cpp` file:

* Reads the corresponding JSON (`nlohmann/json` used for parsing)
* Creates the Protobuf objects
* Serializes to a `.bin` file (one file containing all 10 samples)

---

3. **Bazel setup**

`MODULE.bazel`:

```python
module(name = "prototest")

bazel_dep(name = "protobuf", version = "29.0")
```

`BUILD` example:

```python
cc_binary(
    name = "first_writer",
    srcs = ["first_writer.cpp", "first.pb.cc"],
    deps = ["@protobuf//:protobuf"],
)
cc_binary(
    name = "second_writer",
    srcs = ["second_writer.cpp", "second.pb.cc"],
    deps = ["@protobuf//:protobuf"],
)
cc_binary(
    name = "third_writer",
    srcs = ["third_writer.cpp", "third.pb.cc"],
    deps = ["@protobuf//:protobuf"],
)
```

---

4. **Compile & Run**

```bash
bazel build //:first_writer
bazel build //:second_writer
bazel build //:third_writer

./bazel-bin/first_writer
./bazel-bin/second_writer
./bazel-bin/third_writer
```

Output:

```
Protobuf binary written to first_output.bin
Protobuf binary written to second_output.bin
Protobuf binary written to third_output.bin
```

---

## File Sizes Comparison

| Scheme | JSON Size | Protobuf Size |
| ------ | --------- | ------------- |
| First  | 2 KB      | 1 KB          |
| Second | 2.3 KB    | 1.3 KB        |
| Third  | 3.5 KB    | 1.9 KB        |

* Protobuf binaries are smaller than JSON due to compact serialization.
* All 10 sample records are saved in the same binary file for comparison.

---
