#include "Game/gameDragonChallengeMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(DragonChallengeMgr)

// NON_MATCHING: the original stores _12c and the timer separately, before mFlags
DragonChallengeMgr::DragonChallengeMgr() {
    mFlags = 0;
    sub_71006F9720();
    {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        mTimer.rate = 0;
    }
}

// NON_MATCHING: the original reads mRefCount (a discarded volatile load) first
DragonChallengeMgr::~DragonChallengeMgr() = default;

s32 DragonChallengeMgr::incrementRef() {
    return mRefCount.fetchAdd(1);
}

void DragonChallengeMgr::resetTimerRate() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mTimer.rate = 0;
}

s32 DragonChallengeMgr::decrementRef() {
    const s32 previous = mRefCount.fetchSub(1);
    if (previous == 1) {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        mHandles[0].fadeXLink();
        mHandles[1].fadeXLink();
        mHandles[2].fadeXLink();
    }
    return previous;
}

void DragonChallengeMgr::emitXLink(u32 idx) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (mActor && mProcLink.hasProc() && mRefCount.load() != 0) {
        const bool has_proc = mProcLink.hasProc();
        if (idx > 2 || !has_proc)
            return;
        const sead::SafeArray<sead::SafeString, 3> names = {{"DLC2_DragonHorn_Blue",
                                                            "DLC2_DragonHorn_Failure",
                                                            "DLC2_DragonHorn_Orange"}};
        xlinkSearchAndEmit(mActor, names[idx].cstr(), 2, &mHandles[idx]);
    }
}

void DragonChallengeMgr::x_0(u32 idx) {
    emitXLink(idx);
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (mProcLink.hasProc() && mRefCount.load() != 0) {
        const bool has_proc = mProcLink.hasProc();
        if (idx > 2 || !has_proc)
            return;
        auto& handle = mHandles[idx];
        if (handle.sub_7101241B6C())
            handle.sub_7101241A44(_fc);
    }
}

void DragonChallengeMgr::setAllFlags(bool on) {
    mFlags = on ? 0xffffffff : 0;
}

void DragonChallengeMgr::setFlag(u32 idx) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (idx > 4)
        return;
    mFlags |= 1u << idx;
}

void DragonChallengeMgr::resetFlag(u32 idx) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (idx > 4)
        return;
    mFlags &= ~(1u << idx);
}

// NON_MATCHING: register assignment (the original reuses the `this` register for the result)
bool DragonChallengeMgr::isFlagSet(u32 idx) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    bool result;
    if (idx > 4)
        result = false;
    else
        result = (mFlags & (1u << idx)) != 0;
    return result;
}

void DragonChallengeMgr::setFlag(u32 idx, bool on) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (idx > 4)
        return;
    if (on)
        mFlags |= 1u << idx;
    else
        mFlags &= ~(1u << idx);
}

bool DragonChallengeMgr::isTimerStopped() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    return mTimer.rate == -1.0f;
}

void DragonChallengeMgr::startTimer(f32 value) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mTimer = ksys::Timer(value, value);
}

bool DragonChallengeMgr::updateTimer() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mTimer.update();
    return mTimer.value <= sead::Mathf::epsilon();
}

}  // namespace uking
