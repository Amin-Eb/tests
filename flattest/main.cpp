#include <iostream>
#include "monster_generated.h"
#include "flatbuffers/flatbuffers.h"

using namespace MyGame::Sample;

int main() {
    flatbuffers::FlatBufferBuilder builder;

    auto name = builder.CreateString("Orc");
    MonsterBuilder monster(builder);
    monster.add_name(name);
    monster.add_hp(80);
    auto orc = monster.Finish();
    builder.Finish(orc);

    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize();

    auto monster_ptr = GetMonster(buf);
    std::cout << "Monster name: " << monster_ptr->name()->c_str() << std::endl;
    std::cout << "HP: " << monster_ptr->hp() << std::endl;

    return 0;
}

