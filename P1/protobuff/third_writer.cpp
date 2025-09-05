#include "third.pb.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace sample;

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::ifstream jf("../json/third.json");
    json data;
    jf >> data;

    PeopleThird people;

    for (auto &p : data) {
        PersonThird* person = people.add_people();
        person->set_name(p["name"].get<std::string>());

        Born3* born = person->mutable_born();
        born->set_date(p["born"]["date"].get<std::string>());
        born->set_city(p["born"]["city"].get<std::string>());
        born->set_hospital_name(p["born"]["hospital_name"].get<std::string>());
        born->set_father_name(p["born"]["father_name"].get<std::string>());

        for (auto &c : p["cars"]) {
            Car3* car = person->add_cars();
            car->set_model_name(c["model_name"].get<std::string>());
            car->set_factory_year(c["factory_year"].get<int>());
            car->set_license_plate(c["license_plate"].get<std::string>());
        }

        for (auto &h : p["homes"]) {
            Home3* home = person->add_homes();
            home->set_address(h["address"].get<std::string>());
            home->set_ownership(h["ownership"].get<std::string>());
        }
    }

    std::ofstream out("out/third_proto.bin", std::ios::binary);
    people.SerializeToOstream(&out);
    out.close();

    std::cout << "Written third_proto.bin \n";
    google::protobuf::ShutdownProtobufLibrary();
}

