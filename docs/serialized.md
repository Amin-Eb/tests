Write serializer with flatbuffers, protobuf, csv(or json), binary with your own mechanism.

which one is easier to change from first to third?

which one take less size?

which can have more throughput with same cpu usage?

First:
name
born { date, city}
car { model name, factory year, license plate}
home {address, ownership}
job

Second:
name
born { date, city, hospital name, father name}
car { model name, factory year, license plate}
home {address, ownership}

Third:
name
born { date, city, hospital name, father name}
cars [{ model name, factory year, license plate}, ...]
homes [{address, ownership}, ...]