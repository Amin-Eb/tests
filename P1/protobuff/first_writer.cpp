#include "first.pb.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace sample;

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::ifstream jf("../json/first.json");
    json data;
    jf >> data;

    PeopleFirst people;

    for (auto &p : data) {
        PersonFirst* person = people.add_people();
        person->set_name(p["name"].get<std::string>());

        Born* born = person->mutable_born();
        born->set_date(p["born"]["date"].get<std::string>());
        born->set_city(p["born"]["city"].get<std::string>());

        Car* car = person->mutable_car();
        car->set_model_name(p["car"]["model_name"].get<std::string>());
        car->set_factory_year(p["car"]["factory_year"].get<int>());
        car->set_license_plate(p["car"]["license_plate"].get<std::string>());

        Home* home = person->mutable_home();
        home->set_address(p["home"]["address"].get<std::string>());
        home->set_ownership(p["home"]["ownership"].get<std::string>());

        person->set_job(p["job"].get<std::string>());
    }

    std::ofstream out("out/first_proto.bin", std::ios::binary);
    people.SerializeToOstream(&out);
    out.close();

    std::cout << "Written first_proto.bin \n";
    google::protobuf::ShutdownProtobufLibrary();
}

