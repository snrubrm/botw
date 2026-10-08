#include <cstdarg>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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
    _279 = 0;
    _270.set(0.0f, 0.0f);
    _254 = -1.0f;
    _268 = 0;
    _260 = 0;
    _258.set(0.0f, 0.0f);
}

void Rideable::m24() {
    RideableBase::_8 &= ~0x400u;
}

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

HorseReins* Rideable::m40() {
    return nullptr;
}

void Rideable::m42(int a1) {}

void Rideable::sub_7100E7EAD8(s32 level, const char* format, ...) {
    std::va_list args;
    va_start(args, format);
    va_end(args);
}

void Rideable::sub_7100E7EF1C() {
    xlinkSearchAndEmit(RideableBase::mActor, "Attached", 2, nullptr);
    xlinkSearchAndEmit(RideableBase::mActor, "mc_HorseSoothe", 2, nullptr);
}

f32 Unk_7100e8b2b8::procLink13() {
    return 0.0f;
}

}  // namespace uking::act
