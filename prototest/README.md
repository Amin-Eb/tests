folder of running sample serialization using protobuff

after writing Protocol Buffers in .proto file
we compile it as :
protoc --cpp_out=. addressbook.proto

then setting MODULE.bazel and BUILD files for our build system, bazel
after that we can build the final binary : (due to internet problems i set tor proxy so i use proxychains4 befor actual command)
[proxychains4] bazel build :proto_sample

and finally:

bazel run //:proto_sample addressbook.proto
