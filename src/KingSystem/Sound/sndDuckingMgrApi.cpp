#include "KingSystem/Sound/sndSound.h"

namespace ksys::snd {

bool DuckingMgr::Ducker::isActive() const {
    return _c8 & 1;
}

// 0x7101041f4c (placeholder name): suspends every ducker whose flag bit 1 is set, then clears the flag.
void DuckingMgr::sub_7101041F4C() {
    for (auto it = DuckerType::begin(); it != DuckerType::end(); ++it) {
        Ducker& ducker = mDuckers[*it];
        // Bit 1 asks for a suspend; the original clears bit 0 here.
        if (ducker._c8 & 2) {
            Ducker& d = mDuckers[*it];
            d._c8 &= ~1;
            d.mDucker.suspend();
        }
    }
    if (_20)
        _20 = false;
}

void DuckingMgr::calc() {
    for (auto& ducker : mDuckers)
        ducker.calc();
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
