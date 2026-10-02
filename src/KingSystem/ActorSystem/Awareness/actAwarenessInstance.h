#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Placeholder name (vtable 0x71024dce08): base class of the four sensor objects an
// AwarenessInstance owns (created in 0x7100d7b974; derived vtables e.g. 0x71024dcea8).
// TODO: incomplete.
class Unk_71024dce08 {
public:
    virtual ~Unk_71024dce08();

    /* 0x08 */ u8 _8[0x4c - 0x8];
    /* 0x4c */ f32 _4c;
    /* 0x50 */ u8 _50;
};

// FIXME. The per-actor awareness object (Actor::mAwareness, Actor+0x550). CSV names some of its
// methods "ActorAwareness::*".
class AwarenessInstance {
public:
    AwarenessInstance();
    virtual ~AwarenessInstance();

    void calcForEvent();
    void calc();
    void calc2();

    void sleep();
    void disable();
    bool enable();
    void sub_7100D7C494();
    void sub_7100D7EBE0(f32 value);
    void sub_7100D7EC14(int idx, f32 value);
    f32 sub_7100D7EC34(int idx) const;

    u8 _8[0x260 - 0x8];
    sead::SafeArray<Unk_71024dce08*, 4> _260;
    u8 _280[0x334 - 0x280];
    s8 _334;
    u32 _338;
};
KSYS_CHECK_SIZE_NX150(AwarenessInstance, 0x340);

}  // namespace ksys::act
