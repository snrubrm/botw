#include "KingSystem/Sound/sndSound.h"

namespace ksys::snd {

// 0x710103e404
DuckingMgr::DuckingMgr() = default;

// 0x710103e424: frees the ducker array and destroys its heap.
DuckingMgr::~DuckingMgr() {
    mDuckers.freeBuffer();
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
}

// 0x710103dce4: finalizes the group ducker; the member destructor then releases it.
DuckingMgr::Ducker::~Ducker() {
    mDucker.finalize();
}

// NON_MATCHING: the original spills the state local to the stack (store + reload) before testing it, ours keeps
// it in a register (8 bytes shorter).
// 0x710103df60: per-frame update. While inactive and idle it releases the group ducker; otherwise it accumulates
// the ducking time and ends the ducking once the configured duration has passed.
void DuckingMgr::Ducker::calc() {
    if (!(_c8 & 1)) {
        const s32 state = mDucker.getState();
        if (state == 0) {
            if (_b0)
                return;
            if (!mDucker.isInitialized())
                return;
            mDucker.removeAndDestroyAllTargets();
            mDucker.finalize();
            return;
        }
    }
    mDucker.calc();
    _c0 += sub_710105E3A4();
    if (!_b0)
        return;
    const f32 duration = _b0->mDuration;
    if (duration > 0.0f && duration > _c0)
        return;
    _c8 &= ~1;
}

// NON_MATCHING: the original keeps `this` in x19 and computes &mDucker for the tail call, ours keeps `this` in
// x20 and precomputes &mDucker (8 bytes larger).
// 0x710103e2dc (placeholder name): restarts the ducking for `f` when the group's volume is low enough.
void DuckingMgr::Ducker::sub_710103E2DC(f32 f) {
    if (_c4 > f) {
        if (u32(mDucker.getState()) < 2)
            return;
        if (_b0) {
            const f32 duration = _b0->mDuration;
            if (duration > 0.0f) {
                const f32 remaining = duration - _c0;
                sub_710103E020(f);
                if (remaining > 0.0f)
                    mDucker.getSettings()._0 = remaining;
                mDucker.resetState();
                return;
            }
        }
    }
    sub_710103E020(f);
    mDucker.resetState();
}

void DuckingMgr::Ducker::activateMaybe() {
    _c8 |= 1;
    _c0 = 0;
}

void DuckingMgr::Ducker::deactivateMaybe(bool suspend) {
    _c8 &= ~1;
    if (suspend)
        mDucker.suspend();
}

void DuckingMgr::Ducker::activateAndResetMaybe() {
    _c8 |= 1;
    _c0 = 0;
    mDucker.resetState();
}

// Whether the ducker is still ducking: active, and either just started or ducking (state 1 or 2)
// with a target fader still moving.
bool DuckingMgr::Ducker::sub_710103E368() const {
    if (!(_c8 & 1))
        return false;
    if (_c0 == 0)
        return true;
    const s32 state = mDucker.getState();
    if (state != 1 && state != 2)
        return false;
    const s32 num = mDucker.getTargetNum();
    for (s32 i = 0; i < num; ++i) {
        if (mDucker.getTarget(i)->isFaderMoving())
            return true;
    }
    return false;
}

}  // namespace ksys::snd
