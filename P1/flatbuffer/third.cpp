#include "third_generated.h"
#include "../Core/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace Sample;

int main() {
    std::ifstream jf("../json/third.json");
    json data;
    jf >> data;

    flatbuffers::FlatBufferBuilder builder(1024);

    std::vector<flatbuffers::Offset<PersonThird>> people_vec;

    for (auto &p : data) {
        auto name = builder.CreateString(p["name"].get<std::string>());

        auto born = CreateBorn3(
            builder,
            builder.CreateString(p["born"]["date"].get<std::string>()),
            builder.CreateString(p["born"]["city"].get<std::string>()),
            builder.CreateString(p["born"]["hospital_name"].get<std::string>()),
            builder.CreateString(p["born"]["father_name"].get<std::string>())
        );

        std::vector<flatbuffers::Offset<Car3>> cars_vec;
        for (auto &c : p["cars"]) {
            cars_vec.push_back(CreateCar3(
                builder,
                builder.CreateString(c["model_name"].get<std::string>()),
                c["factory_year"].get<int32_t>(),
                builder.CreateString(c["license_plate"].get<std::string>())
            ));
        }
        auto cars = builder.CreateVector(cars_vec);

        std::vector<flatbuffers::Offset<Home3>> homes_vec;
        for (auto &h : p["homes"]) {
            homes_vec.push_back(CreateHome3(
                builder,
                builder.CreateString(h["address"].get<std::string>()),
                builder.CreateString(h["ownership"].get<std::string>())
            ));
        }
        auto homes = builder.CreateVector(homes_vec);

        auto person = CreatePersonThird(builder, name, born, cars, homes);
        people_vec.push_back(person);
    }

    auto people = builder.CreateVector(people_vec);
    builder.Finish(people);

    std::ofstream out("out/third_output.bin", std::ios::binary);
    out.write(reinterpret_cast<const char *>(builder.GetBufferPointer()), builder.GetSize());
    out.close();

    std::cout << "FlatBuffer written to third_output.bin\n";
}
