folder of running sample serialization using **flatBuffers**
flatBuffers is installable from snapcraft.io
official site: https://flatbuffers.dev
after writing Protocol Buffers in .fbs file we compile it as :
```
flatc --cpp monster.fbs
```
the cpp code can be compiled using g++, just remember the include directory of faltbuffer
```
g++ main.cpp -o main -I/path/to/flatbuffers/include
```
now we can see the result just by:
```
./main
```
