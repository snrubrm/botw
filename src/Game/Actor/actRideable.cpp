#include "Game/Actor/actRideable.h"

namespace uking::act {

Rideable::Rideable() = default;

Rideable::~Rideable() = default;

// NON_MATCHING: the original clears _1bc / _1c0 with one 8-byte store at a 4-aligned address
void Rideable::m6() {
    Unk_7100e8b2b8::m6();
    _1bc = 0;
    _1c0 = 0;
    _248 = 0;
    _278 = 0;
    _270.set(0.0f, 0.0f);
    _254 = -1.0f;
    _268 = 0;
    _260 = 0;
    _258.set(0.0f, 0.0f);
}

void Rideable::m24() {
    RideableBase::_8 &= ~0x400u;
}

HorseReins* Rideable::m40() {
bool Rideable::m44() {
    const Gear gear(_18._b == 0 ? _18._9 : _18._b);
    return int(gear) > 1;
}

Rideable::Gear Rideable::m23() {
    const Gear target(_168);
    const Gear gear(_18._b == 0 ? _18._9 : _18._b);
    if (int(target) <= 2 && int(gear) == int(target))
        return Gear(3);
    return gear;
}

void* Rideable::m40() {
    return nullptr;
}

void Rideable::m42(int a1) {}

}  // namespace uking::act
