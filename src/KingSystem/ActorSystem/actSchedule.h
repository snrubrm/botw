#pragma once

#include <basis/seadTypes.h>
#include <thread/seadAtomic.h>

namespace ksys::act {

// Actor::mSchedule (the actor's schedule; the CSV has no names for it). TODO: incomplete (size unknown).
class Schedule {
public:
    /* 0x000 */ u8 _0[0x124];
    /* 0x124 */ sead::Atomic<bool> _124;  // near trigger enabled (ChangeEnableNearTrigger behavior)
};

}  // namespace ksys::act
