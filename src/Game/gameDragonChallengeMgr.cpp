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

// NON_MATCHING: branch layout of the validity checks
void DragonChallengeMgr::emitXLink(int idx) {
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

// NON_MATCHING: branch layout of the validity checks
void DragonChallengeMgr::x_0(int idx) {
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

void DragonChallengeMgr::setFlag(int idx) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (idx <= 4)
        mFlags |= 1u << idx;
}

void DragonChallengeMgr::resetFlag(int idx) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (idx <= 4)
        mFlags &= ~(1u << idx);
}

// NON_MATCHING: register assignment (the out-of-range result is a separate block in the original)
bool DragonChallengeMgr::isFlagSet(int idx) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    bool result = false;
    if (idx <= 4)
        result = mFlags & (1u << idx);
    return result;
}

void DragonChallengeMgr::setFlag(int idx, bool on) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (idx <= 4) {
        if (on)
            mFlags |= 1u << idx;
        else
            mFlags &= ~(1u << idx);
    }
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
