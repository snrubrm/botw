#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::act {

// Actor::mSchedule (the actor's schedule; the CSV has no names for it). TODO: incomplete (size unknown).
class Schedule {
public:
    // 0x7100D192C0: ActLink passes the actor's schedule, a nullable iterator, name and bool.
    void sub_7100D192C0(const al::ByamlIter* iter, const char* name, bool value);

    /* 0x000 */ u8 _0[0x68];
    /* 0x068 */ sead::SafeString _68;  // TimelineAI::m34 (the timeline's name; empty when the actor has no schedule)
    /* 0x078 */ u8 _78[0x88 - 0x78];
    /* 0x088 */ sead::SafeString _88;  // current timeline key name (lane1 s21: KakarikoKokkoTimeline)
    /* 0x098 */ u8 _98[0xf0 - 0x98];
    /* 0x0f0 */ al::ByamlIter _f0;
    /* 0x100 */ u8 _100[0x120 - 0x100];
    /* 0x120 */ bool _120;  // NPCTimeline::calc_: the timeline name (_68) changed; cleared after handling
    /* 0x121 */ u8 _121;
    /* 0x122 */ bool _122;
    /* 0x123 */ u8 _123;
    /* 0x124 */ sead::Atomic<bool> _124;  // near trigger enabled (ChangeEnableNearTrigger behavior)
    /* 0x125 */ u8 _125[0x12a - 0x125];
    /* 0x12a */ bool _12a;
    /* 0x12b */ u8 _12b;  // NPCTimeline::m36: IsPathRest is also set while this is 0
    /* 0x12c */ u8 _12c[0x160 - 0x12c];
    /* 0x160 */ sead::SafeString _160;  // DynAS name (NPCReturnAnchor: fine weather)
    /* 0x170 */ sead::SafeString _170;  // DynAS name (NPCReturnAnchor: rain / snow / thunderstorm)
    /* 0x180 */ u8 _180[0x1a0 - 0x180];
    /* 0x1a0 */ s32 _1a0;  // NPCTravelBase::sub_71004DF7EC / NPCMove: meeting state values (selected by the weather / flags)
    /* 0x1a4 */ s32 _1a4;
    /* 0x1a8 */ s32 _1a8;
    /* 0x1ac */ u8 _1ac[0x1b0 - 0x1ac];
    /* 0x1b0 */ s32 _1b0;  // NPCTravelBase::sub_71004DF978: the values passed to the DynAS name lookup
    /* 0x1b4 */ s32 _1b4;
    /* 0x1b8 */ s32 _1b8;
    /* 0x1bc */ u8 _1bc[0x248 - 0x1bc];
    /* 0x248 */ sead::SafeString _248;  // NPCAnchorWait::enter_ compares the current animation name with it (fine weather)
    /* 0x258 */ sead::SafeString _258;  // same, for a rain anchor
    /* 0x268 */ u8 _268[0x2ec - 0x268];
    /* 0x2ec */ u32 _2ec;
    /* 0x2f0 */ u32 _2f0;
    /* 0x2f4 */ u8 _2f4[4];
    /* 0x2f8 */ u32 _2f8;  // flags (bit 1 set by KakarikoKokkoTimeline::init_)
};

}  // namespace ksys::act
