#include "first_generated.h"
#include "../Core/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace Sample;

int main() {
    //parsing json data
    std::ifstream jf("../json/first.json");
    json data;
    jf >> data;

    //flatbuffer builder
    flatbuffers::FlatBufferBuilder builder(1024);

    std::vector<flatbuffers::Offset<PersonFirst>> people_vec;

    for (auto &p : data) {
        auto name = builder.CreateString(p["name"].get<std::string>());

        auto born = CreateBorn(
            builder,
            builder.CreateString(p["born"]["date"].get<std::string>()),
            builder.CreateString(p["born"]["city"].get<std::string>())
        );

        auto car = CreateCar(
            builder,
            builder.CreateString(p["car"]["model_name"].get<std::string>()),
            p["car"]["factory_year"].get<int32_t>(),
            builder.CreateString(p["car"]["license_plate"].get<std::string>())
        );

        auto home = CreateHome(
            builder,
            builder.CreateString(p["home"]["address"].get<std::string>()),
            builder.CreateString(p["home"]["ownership"].get<std::string>())
        );

        auto job = builder.CreateString(p["job"].get<std::string>());

        auto person = CreatePersonFirst(builder, name, born, car, home, job);
        people_vec.push_back(person);
    }
    
    auto people = builder.CreateVector(people_vec);
    builder.Finish(people);

    // Save binary
    std::ofstream out("out/first_output.bin", std::ios::binary);
    out.write(reinterpret_cast<const char *>(builder.GetBufferPointer()), builder.GetSize());
    out.close();

    std::cout << "FlatBuffer written to first_output.bin\n";
}
