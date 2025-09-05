# Serialization Comparison Project

This project demonstrates **serialization of structured data** using **JSON**, **FlatBuffers**, and **Protobuf**, comparing **three schemas** of increasing complexity.

## Schemas

1. **First schema (simple)**

   ```text
   name
   born { date, city }
   car { model_name, factory_year, license_plate }
   home { address, ownership }
   job
   ```

2. **Second schema (medium)**

   ```text
   name
   born { date, city, hospital_name, father_name }
   car { model_name, factory_year, license_plate }
   home { address, ownership }
   ```

3. **Third schema (complex)**

   ```text
   name
   born { date, city, hospital_name, father_name }
   cars [ { model_name, factory_year, license_plate }, ... ]
   homes [ { address, ownership }, ... ]
   ```

---

## Serialization Methods

| Method      | Description                                               |
| ----------- | --------------------------------------------------------- |
| JSON        | Text-based, human-readable, easy to modify.               |
| FlatBuffers | Binary, zero-copy, fast access without deserialization.   |
| Protobuf    | Binary, requires code generation, efficient, widely used. |

---

## Comparison Table

| Schema / Method | JSON Size | FlatBuffers Size | Protobuf Size |
| --------------- | --------- | ---------------- | ------------- |
| First           | 2.5 KB    | 2 KB             | 1 KB          |
| Second          | 2.8 KB    | 2.3 KB           | 1.3 KB        |
| Third           | 4 KB      | 3.5 KB           | 1.9 KB        |

---

## Ease of Changing Schema

| Method      | Ease of changing from first → third                  |
| ----------- | ---------------------------------------------------- |
| JSON        | Very easy — just add/remove fields, arrays           |
| FlatBuffers | Medium — need to update `.fbs` schema and recompile  |
| Protobuf    | Medium — need to update `.proto` and regenerate code |

---

## Performance & Throughput

| Method      | Throughput (same CPU usage)               |
| ----------- | ----------------------------------------- |
| JSON        | Lowest — text parsing overhead, not binary|
| FlatBuffers | Highest — zero-copy, direct memory access |
| Protobuf    | High — binary, but needs deserialization* |

*:
  in protobuffer UNLIKE FlatBuffers:
    You cannot access the fields directly from the binary without creating a C++ object.
    This creates extra memory usage and CPU overhead.

---

## Summary

1. **Easiest to modify**: **JSON**
2. **Smallest serialized size**: **Protobuf**
3. **Highest throughput**: **FlatBuffers**

This project shows the trade-offs between **ease of use, size, and speed**. Choosing the right serialization method depends on your **use case**:

* Human-readable data → JSON
* High-performance access → FlatBuffers
* Cross-language, compact storage → Protobuf
