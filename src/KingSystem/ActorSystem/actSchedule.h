#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>

namespace ksys::act {

// Actor::mSchedule (the actor's schedule; the CSV has no names for it). TODO: incomplete (size unknown).
class Schedule {
public:
    /* 0x000 */ u8 _0[0x68];
    /* 0x068 */ sead::SafeString _68;  // TimelineAI::m34 (the timeline's name; empty when the actor has no schedule)
    /* 0x078 */ u8 _78[0x88 - 0x78];
    /* 0x088 */ sead::SafeString _88;  // current timeline key name (lane1 s21: KakarikoKokkoTimeline)
    /* 0x098 */ u8 _98[0x120 - 0x98];
    /* 0x120 */ bool _120;  // NPCTimeline::calc_: the timeline name (_68) changed; cleared after handling
    /* 0x121 */ u8 _121;
    /* 0x122 */ bool _122;
    /* 0x123 */ u8 _123;
    /* 0x124 */ sead::Atomic<bool> _124;  // near trigger enabled (ChangeEnableNearTrigger behavior)
    /* 0x125 */ u8 _125[0x12b - 0x125];
    /* 0x12b */ u8 _12b;  // NPCTimeline::m36: IsPathRest is also set while this is 0
    /* 0x12c */ u8 _12c[0x2f8 - 0x12c];
    /* 0x2f8 */ u32 _2f8;  // flags (bit 1 set by KakarikoKokkoTimeline::init_)
};

}  // namespace ksys::act
