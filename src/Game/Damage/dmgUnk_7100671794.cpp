#include "Game/Damage/dmgUnk_7100671794.h"
#include <prim/seadScopedLock.h>

namespace uking::dmg {

bool Unk_7100671794::sub_7100671A40(ksys::act::BaseProc* proc, s32 frames) {
    if (_c0 > 0.0f)
        return false;
    _c0 = f32(frames);
    return true;
}

bool Unk_7100671794::sub_7100671A64(ksys::act::BaseProc* proc) const {
    return _c0 <= 0.0f;
}

bool Unk_7100671794::sub_7100671ED8(ksys::act::BaseProc* proc) {
    return mEntries[0].mLink.hasProcById(proc) || mEntries[1].mLink.hasProcById(proc) ||
           mEntries[2].mLink.hasProcById(proc) || mEntries[3].mLink.hasProcById(proc) ||
           mEntries[4].mLink.hasProcById(proc) || mEntries[5].mLink.hasProcById(proc) ||
           mEntries[6].mLink.hasProcById(proc) || mEntries[7].mLink.hasProcById(proc);
}

bool Unk_7100671794::sub_7100671F78(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_cc);
    bool found = false;
    for (int i = 0; i < 8; ++i) {
        found |= mEntries[i].mLink.hasProcById(proc);
        if (found) {
            if (i <= 6) {
                auto& next = mEntries[i + 1];
                mEntries[i].mLink = next.mLink;
                mEntries[i].mDistance = next.mDistance;
                mEntries[i]._14 = next._14;
            } else {
                mEntries[i].mLink.reset();
            }
        }
    }
    return found;
}

void Unk_7100671794::sub_71006720C8(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_d0);
    _c4 = -1;
}

}  // namespace uking::dmg
