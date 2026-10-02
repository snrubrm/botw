#pragma once

#include <basis/seadTypes.h>
#include <thread/seadAtomic.h>

namespace ksys::act {

// Actor::mSchedule (the actor's schedule; the CSV has no names for it). TODO: incomplete (size unknown).
class Schedule {
public:
    /* 0x000 */ u8 _0[0x124];
    /* 0x124 */ sead::Atomic<bool> _124;  // near trigger enabled (ChangeEnableNearTrigger behavior)
    /* 0x125 */ u8 _125[0x2f8 - 0x125];
    /* 0x2f8 */ u32 _2f8;  // flags (bit 1 set by KakarikoKokkoTimeline::init_)
};

}  // namespace ksys::act
