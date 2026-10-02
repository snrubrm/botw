#pragma once

#include <basis/seadTypes.h>
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
