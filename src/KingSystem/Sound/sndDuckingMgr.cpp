#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

bool DuckingMgr::Ducker::isActive() const {
    return _c8 & 1;
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
