#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

// Placeholder name = its out-of-line constructor (0x710071edf8). Embedded in PreyRoot (0x1c0) and
// uking::act::WolfLink (0x14c8).
class Unk_710071edf8 {
public:
    explicit Unk_710071edf8(ksys::act::Actor* actor);

    ksys::act::Actor* mActor;
    void* _8 = nullptr;
    void* _10 = nullptr;
    void* _18 = nullptr;
    u16 _20 = 0;
    f32 _24 = 45.0f;
    f32 _28 = 120.0f;
    f32 _2c = 450.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_710071edf8, 0x30);

// Free helpers in the same TU (0x710071e000-0x710071f000).
// True while the event "Demo648_0" (entry point name at 0x7101da3652, empty) is active.
bool sub_710071E208();
// Sets or clears flag 0x80000 of the actor's phys::InstanceSet (clears it when a2 is true).
void sub_710071EDD0(ksys::act::Actor* actor, bool a2);
// 0x710071eb88 (lane1 s43): sub_71005DD798(actor, 0x13, nullptr, 0, 0) (false without an actor).
bool sub_710071EB88(ksys::act::Actor* actor);
// 0x710071edac (lane1 s43): the actor has physics and bit 0x80000 of its flags is clear.
bool sub_710071EDAC(ksys::act::Actor* actor);
// Calls sub_71005DB068(actor, sub_71005D960C(actor)) for a non-null actor.
void sub_710071EB3C(ksys::act::Actor* actor);

// 0x710071e600: XZ distance from the recovered stage center, scaled stage radius.
bool sub_710071E600(const sead::Vector3f* pos, f32 radius_rate);

class Unk_7102450fa8;
// 0x710071e64c: actor damage-state predicate; PriestBossActorEnemyRoot::m35
// passes the RTTI-checked battle unit, whose flags+78 are also read by this callee.
bool sub_710071E64C(ksys::act::Actor* actor, Unk_7102450fa8* unit);
