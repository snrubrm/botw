#include "KingSystem/Sound/sndSound.h"

namespace ksys::snd {

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

bool DuckingMgr::Ducker::isActive() const {
    return _c8 & 1;
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

DuckingMgr::Ducker* DuckingMgr::sub_7101042024(DuckerType type) {
    Ducker& ducker = mDuckers[type];
    ducker._c8 |= 1;
    ducker._c0 = 0;
    return &mDuckers[type];
}

void DuckingMgr::sub_7101042D6C(DuckerType type, bool suspend) {
    Ducker& ducker = mDuckers[type];
    ducker._c8 &= ~1;
    if (suspend)
        ducker.mDucker.suspend();
}

DuckingMgr::Ducker* DuckingMgr::startDucking(const sead::SafeString& type) {
    for (auto it = DuckerType::begin(); it != DuckerType::end(); ++it) {
        if (type.isEqual((*it).text())) {
            Ducker& ducker = mDuckers[*it];
            ducker._c8 |= 1;
            ducker._c0 = 0;
            return &mDuckers[*it];
        }
    }
    return nullptr;
}

void DuckingMgr::sub_7101042DB4(const sead::SafeString& type, bool suspend) {
    for (auto it = DuckerType::begin(); it != DuckerType::end(); ++it) {
        if (type.isEqual((*it).text())) {
            Ducker& ducker = mDuckers[*it];
            ducker._c8 &= ~1;
            if (suspend)
                ducker.mDucker.suspend();
            return;
        }
    }
}

}  // namespace ksys::snd
