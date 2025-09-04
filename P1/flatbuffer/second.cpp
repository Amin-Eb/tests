#include "second_generated.h"
#include "../Core/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace Sample;

int main() {
    std::ifstream jf("../json/second.json");
    json data;
    jf >> data;

    flatbuffers::FlatBufferBuilder builder(1024);

    std::vector<flatbuffers::Offset<PersonSecond>> people_vec;

    for (auto &p : data) {
        auto name = builder.CreateString(p["name"].get<std::string>());

        auto born = CreateBorn2(
            builder,
            builder.CreateString(p["born"]["date"].get<std::string>()),
            builder.CreateString(p["born"]["city"].get<std::string>()),
            builder.CreateString(p["born"]["hospital_name"].get<std::string>()),
            builder.CreateString(p["born"]["father_name"].get<std::string>())
        );

        auto car = CreateCar2(
            builder,
            builder.CreateString(p["car"]["model_name"].get<std::string>()),
            p["car"]["factory_year"].get<int32_t>(),
            builder.CreateString(p["car"]["license_plate"].get<std::string>())
        );

        auto home = CreateHome2(
            builder,
            builder.CreateString(p["home"]["address"].get<std::string>()),
            builder.CreateString(p["home"]["ownership"].get<std::string>())
        );

        auto person = CreatePersonSecond(builder, name, born, car, home);
        people_vec.push_back(person);
    }

    auto people = builder.CreateVector(people_vec);
    builder.Finish(people);

    std::ofstream out("out/second_output.bin", std::ios::binary);
    out.write(reinterpret_cast<const char *>(builder.GetBufferPointer()), builder.GetSize());
    out.close();

    std::cout << "FlatBuffer written to second_output.bin\n";
}
