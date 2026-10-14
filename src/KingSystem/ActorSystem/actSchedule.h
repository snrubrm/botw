#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace sead {
class Heap;
}

namespace ksys::res {
class Handle;
}

namespace ksys::act {

class Actor;

// Actor::mSchedule (the actor's schedule; the CSV calls its functions ActorQuestLink::*). Vtable 0x71024d8e90
// (D1, D0, allocRes, freeRes); size 0x300 (lane4 s85: layout from the constructor 0x7100d18fd0).
class Schedule {
public:
    // 0x7100d18fd0 (CSV ActorQuestLink::ctor)
    explicit Schedule(Actor* actor);
    virtual ~Schedule() = default;
    // 0x7100d19178 (CSV ActorQuestLink::allocRes): records the heap and allocates the resource handle.
    virtual bool allocRes(sead::Heap* heap);
    // 0x7100d191c4 (placeholder name): destroys the resource handle allocated by allocRes.
    virtual void freeRes();

    // 0x7100d19210 (CSV ActorQuestLink::reset)
    void reset();
    // 0x7100D192C0: ActLink passes the actor's schedule, a nullable iterator, name and bool.
    void sub_7100D192C0(const al::ByamlIter* iter, const char* name, bool value);
    // 0x7100d1aad8 (placeholder name): selects the current timeline (_d0): the last conditional timeline whose
    // "Condition" flag is set, else the default one; true when it changed.
    bool sub_7100D1AAD8();
    // 0x7100d1c27c (1052 B, declaration only; placeholder name): checks the "Near" trigger parameters.
    bool sub_7100D1C27C(const al::ByamlIter* params, bool active);
    // 0x7100d1c698 (declaration only, 356 bytes; placeholder name): read by act::x_6.
    bool sub_7100D1C698();

    /* 0x008 */ Actor* mActor;
    /* 0x010 */ sead::FixedSafeString<64> _10;
    /* 0x068 */ sead::SafeString _68;  // TimelineAI::m34 (the timeline's name; empty when the actor has no schedule)
    /* 0x078 */ const char* _78 = &sead::SafeString::cNullChar;
    /* 0x080 */ s32 _80 = -1;
    /* 0x088 */ sead::SafeString _88;  // current timeline key name (lane1 s21: KakarikoKokkoTimeline)
    /* 0x098 */ sead::SafeString _98;
    /* 0x0a8 */ sead::SafeString _a8;
    /* 0x0b8 */ sead::SafeString _b8;
    /* 0x0c8 */ u32 _c8 = 0;
    /* 0x0d0 */ al::ByamlIter _d0;
    /* 0x0e0 */ al::ByamlIter _e0;
    /* 0x0f0 */ al::ByamlIter _f0;
    /* 0x100 */ al::ByamlIter _100;
    /* 0x110 */ al::ByamlIter _110;
    /* 0x120 */ bool _120 = false;  // NPCTimeline::calc_: the timeline name (_68) changed; cleared after handling
    /* 0x121 */ u8 _121 = 0;
    /* 0x122 */ bool _122 = false;
    /* 0x123 */ bool _123 = false;  // the "Near" trigger fired (sub_7100D192C0)
    /* 0x124 */ sead::Atomic<bool> _124{sead::AtomicDirectInitTag{}, false};  // near trigger enabled (ChangeEnableNearTrigger behavior)
    /* 0x125 */ u8 _125 = 0;
    /* 0x126 */ u8 _126 = 0;
    /* 0x127 */ u8 _127 = 0;
    /* 0x128 */ u8 _128 = 0;
    /* 0x129 */ u8 _129 = 0;
    /* 0x12a */ bool _12a = false;
    /* 0x12b */ u8 _12b = 0;  // NPCTimeline::m36: IsPathRest is also set while this is 0
    /* 0x130 */ sead::Heap* mHeap = nullptr;
    /* 0x138 */ res::Handle* mResHandle = nullptr;
    /* 0x140 */ sead::SafeString _140;
    /* 0x150 */ sead::SafeString _150;
    /* 0x160 */ sead::SafeString _160;  // DynAS name (NPCReturnAnchor: fine weather)
    /* 0x170 */ sead::SafeString _170;  // DynAS name (NPCReturnAnchor: rain / snow / thunderstorm)
    /* 0x180 */ sead::SafeString _180;
    /* 0x190 */ sead::SafeString _190;
    /* 0x1a0 */ s32 _1a0 = 0;  // NPCScheduleMove::sub_71004DF7EC / NPCMove: meeting state values (selected by the weather / flags)
    /* 0x1a4 */ s32 _1a4 = 0;
    /* 0x1a8 */ s32 _1a8 = 0;
    /* 0x1ac */ s32 _1ac = 0;
    /* 0x1b0 */ s32 _1b0 = 0;  // NPCScheduleMove::sub_71004DF978: the values passed to the DynAS name lookup
    /* 0x1b4 */ s32 _1b4 = 0;
    /* 0x1b8 */ s32 _1b8 = 0;
    /* 0x1bc */ s32 _1bc = 0;
    /* 0x1c0 */ s32 _1c0 = 0;
    /* 0x1c4 */ s32 _1c4 = 0;
    /* 0x1c8 */ s32 _1c8 = 60;
    /* 0x1cc */ s32 _1cc = -1;
    /* 0x1d0 */ s32 _1d0 = -1;
    /* 0x1d4 */ s32 _1d4 = 5;
    /* 0x1d8 */ sead::SafeString _1d8;
    /* 0x1e8 */ sead::SafeString _1e8;
    /* 0x1f8 */ sead::SafeString _1f8;
    /* 0x208 */ sead::SafeString _208;
    /* 0x218 */ sead::SafeString _218;
    /* 0x228 */ sead::SafeString _228;
    /* 0x238 */ sead::SafeString _238;
    /* 0x248 */ sead::SafeString _248;  // NPCAnchorWait::enter_ compares the current animation name with it (fine weather)
    /* 0x258 */ sead::SafeString _258;  // same, for a rain anchor
    /* 0x268 */ sead::SafeString _268;
    /* 0x278 */ sead::SafeString _278;
    /* 0x288 */ sead::SafeString _288;
    /* 0x298 */ sead::SafeString _298;
    /* 0x2a8 */ sead::SafeString _2a8;
    /* 0x2b8 */ sead::SafeString _2b8;
    /* 0x2c8 */ sead::SafeString _2c8;
    /* 0x2d8 */ sead::SafeString _2d8;
    /* 0x2e8 */ u32 _2e8 = 0;
    /* 0x2ec */ u32 _2ec = 0;
    /* 0x2f0 */ u32 _2f0 = 0;
    /* 0x2f4 */ u32 _2f4 = 0;
    /* 0x2f8 */ u32 _2f8 = 0;  // flags (bit 1 set by KakarikoKokkoTimeline::init_)
    /* 0x2fc */ u32 _2fc = 0;
};
KSYS_CHECK_SIZE_NX150(Schedule, 0x300);

}  // namespace ksys::act
