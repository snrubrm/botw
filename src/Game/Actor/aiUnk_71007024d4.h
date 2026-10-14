#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
}

// Placeholder names (no RTTI, no vtable of its own: the original has no vtable for this class).
//
// An actor "rain" component: a pool of actors (BaseProcLink + BaseProcHandle pairs) that are
// created around the player when a timer runs out. The embedded users are
// GanonBeastRoot + 0x50 (Unk_71023f18e8, vtable 0x71023f18e8) and the object at DamageInfoMgr + 0x7b0
// (vtable 0x710243c3a0); both share m0 / m4 and use the default m5 / m6 of this class.
// Methods of this class are spread over two translation units of the original: the virtual
// functions m0 / m4 / m5 / m6 (0x71007024d4 - 0x7100702844) and the non-virtual ones
// (0x71007107cc - 0x7100710e94).
class Unk_71007024d4 {
public:
    struct Entry {
        ksys::act::BaseProcLink link;
        ksys::act::BaseProcHandle handle;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x20);

    // 0x71007024d4: picks a spawn position around m6(): `m6() + (m4() direction on the XZ plane) *
    // _30` plus `_34` height, then a random offset (m5) on a circle; tries twice when the result is
    // closer than `_3c` to the base position and keeps the farther one.
    virtual bool m0(sead::Vector3f* out);
    // Gets the position around which actors are created.
    virtual bool m1(sead::Vector3f* out) = 0;
    // Gets the name of the actor to create (returns whether it is not empty).
    virtual bool m2(sead::BufferedSafeString* out) = 0;
    // Called with a newly created actor.
    virtual void m3(ksys::act::Actor* actor) = 0;
    // 0x7100702844: the camera look direction (ksys::sub_7100D8C7FC).
    virtual bool m4(sead::Vector3f* out);
    // 0x710070277c: random offset: `radius` in [0, _38), `angle` in radians (whole degrees).
    virtual void m5(f32* radius, f32* angle, const sead::Vector3f* base);
    // 0x710070280c: the player position.
    virtual void m6(sead::Vector3f* out);

    // 0x71007107cc
    bool sub_71007107CC(sead::Heap* heap, s32 count);
    // 0x7100710890: sets the interval range (frames) and restarts the timer.
    void sub_7100710890(s32 min, s32 max);
    // 0x7100710938: the per frame update.
    void sub_7100710938();
    // 0x7100710a5c: requests the creation of every unused entry.
    void sub_7100710A5C(const sead::Vector3f& pos);
    // 0x7100710c14: places a created actor.
    bool sub_7100710C14(const sead::Vector3f& pos);
    // 0x7100710de4 / 0x7100710e3c: two identical functions (resetting every entry).
    void sub_7100710DE4();
    void sub_7100710E3C();

    /* 0x08 */ ksys::Timer _8;
    /* 0x14 */ s32 _14 = 0;
    /* 0x18 */ s32 _18 = 1;
    /* 0x1c */ f32 _1c = 0;
    /* 0x20 */ s32 mCount = 0;
    /* 0x28 */ Entry* mEntries = nullptr;
    /* 0x30 */ f32 _30 = 5.0f;
    /* 0x34 */ f32 _34 = 6.0f;
    /* 0x38 */ f32 _38 = 12.0f;
    /* 0x3c */ f32 _3c = 3.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_71007024d4, 0x40);
