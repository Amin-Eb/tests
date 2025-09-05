# FlatBuffers Serialization


## Steps

1. **Generate sample JSON files**  
   We created three sample JSON files (`first.json`, `second.json`, `third.json`) with 10 entries each for testing.

2. **Define FlatBuffers schemas**  

   ```
   flatbuffers/
   ├─ first.fbs
   ├─ second.fbs
   └─ third.fbs
   ```

3. **Compile schemas**  
   Using `flatc` to generate C++ headers:

   ```bash
   flatc --cpp first.fbs
   flatc --cpp second.fbs
   flatc --cpp third.fbs
   ```

4. **Parse JSON and serialize to FlatBuffers**  
   In each C++ file (`first.cpp`, `second.cpp`, `third.cpp`), we:
   - Load JSON using `nlohmann/json`
   - Build FlatBuffer objects
   - Serialize and save to binary files (`first_output.bin`, `second_output.bin`, `third_output.bin`)

5. **Compile C++ programs**  

   (include pathes are personal, may differ for you)
   ```bash
   g++ first.cpp -o first -I/snap/flatbuffers/1575/include
   g++ second.cpp -o second -I/snap/flatbuffers/1575/include
   g++ third.cpp -o third -I/snap/flatbuffers/1575/include
   ```

6. **Run programs**  

   ```bash
   ./first
   ./second
   ./third
   ```

   Output:

   ```
   FlatBuffer written to first_output.bin
   FlatBuffer written to second_output.bin
   FlatBuffer written to third_output.bin
   ```

   This confirms that the data has been serialized.

## Output Sizes

| File             | Size   |
|-----------------|-------|
| `first_output.bin`  | 2 KB  |
| `second_output.bin` | 2.3 KB |
| `third_output.bin`  | 3.5 KB |

These sizes can be used for further comparison with JSON or other serialization methods.

## Limits

we want to serialize  data of 10 sapmle people in one binary file, so if we want to use flatbuffer it keeps all people in one vector and serializes that vector.
so if data size will be bigger, we have two choices, increase number of binary output files -> Disk limits, serialize all data in one file -> Ram limits.
applying some specific regex between each two serialized data in one binary file may help!
