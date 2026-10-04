#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::act {
class Actor;
}

namespace uking {

// Name from the CSV (DragonChallengeMgr::*; instance pointer 0x71025c88a0, TU 0x71006f94c4 - 0x71006fb000).
// A singleton (size 0x140) that manages the three "DLC2_DragonHorn_*" (Blue / Failure / Orange, index 0 / 1 / 2) xlink
// events of the dragon horn challenge: the actor they are emitted on, a reference count, five state flags (_f8, bit
// 0-4) and a timer. Every member function except the reference count takes the critical section.
// Layout from createInstance; names of the functions are guesses from their bodies.
class DragonChallengeMgr {
    SEAD_SINGLETON_DISPOSER(DragonChallengeMgr)
    DragonChallengeMgr();
    virtual ~DragonChallengeMgr();

public:
    // 0x71006f9720 (declared only): walks a global list and stores a position in `_88`.
    void sub_71006F9720();
    // 0x71006f9a00: decrements the reference count; fades the three xlink handles when it drops to 0. Returns the
    // previous count.
    s32 decrementRef();
    // 0x71006f9a70: emits the xlink event `idx` (0-2) on the actor if there is a reference and a valid actor.
    void emitXLink(u32 idx);
    // 0x71006f9b68 (CSV x_0): emitXLink(idx), then moves the event to `_fc`.
    void x_0(u32 idx);
    // 0x71006f9c00 (CSV x; declared only): fades (or kills) the events of handle `idx`.
    void x(u32 idx, bool a2);
    // 0x71006f9e20 (declared only).
    void sub_71006F9E20();
    // 0x71006f9fdc: sets all the flags to `on`.
    void setAllFlags(bool on);
    // 0x71006f9fe8 / 0x71006fa03c / 0x71006fa090: set / reset / test the flag `idx` (0-4).
    void setFlag(u32 idx);
    void resetFlag(u32 idx);
    bool isFlagSet(u32 idx);
    // 0x71006f9f74 (CSV x_3): sets or resets the flag `idx`.
    void setFlag(u32 idx, bool on);
    // 0x71006fa0f4: whether the timer is stopped (rate == -1).
    bool isTimerStopped();
    // 0x71006fa138: starts the timer with `value`.
    void startTimer(f32 value);
    // 0x71006fa180: updates the timer; true once its value is at most epsilon.
    bool updateTimer();

    /* 0x28 */ ksys::act::Actor* mActor = nullptr;
    /* 0x30 */ ksys::act::BaseProcLink mProcLink;
    /* 0x40 */ sead::Atomic<s32> mRefCount;
    /* 0x48 */ sead::CriticalSection mCS;
    /* 0x88 */ sead::Vector3f _88 = sead::Vector3f::zero;
    /* 0x98 */ sead::SafeArray<Unk_71012419b4, 3> mHandles;
    /* 0xf8 */ u32 mFlags;
    /* 0xfc */ sead::Matrix34f _fc = sead::Matrix34f::ident;
    /* 0x12c */ u32 _12c = 0;
    /* 0x130 */ ksys::Timer mTimer{};
};
KSYS_CHECK_SIZE_NX150(DragonChallengeMgr, 0x140);

}  // namespace uking
