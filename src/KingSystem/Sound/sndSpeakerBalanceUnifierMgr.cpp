#include <aal/aalShape.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

f32 SpeakerBalanceUnifierMgr::sSizeThresholds[3] = {2.0f, 5.0f, 40.0f};

// NON_MATCHING: the original reads the thresholds through a direct adrp of a file-local table that is not constant (it
// is written elsewhere in its translation unit); a never-written local table gets folded, so it is an external member here
// (GOT access).
void SpeakerBalanceUnifierMgr::sub_7101027D4C(f32 size, aal::Shape* shape) {
    if (!mUnifiers.isBufferReady())
        return;
    s32 idx;
    if (sSizeThresholds[0] >= size)
        idx = 0;
    else if (sSizeThresholds[1] >= size)
        idx = 1;
    else if (sSizeThresholds[2] >= size)
        idx = 2;
    else
        idx = 3;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (auto* unifier = mUnifiers.at(idx))
        unifier->addUnifiable(shape);
}

void SpeakerBalanceUnifierMgr::sub_7101027E0C(aal::Shape* shape) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mUnifiers.size(); ++i) {
        if (auto* unifier = mUnifiers.at(i))
            unifier->removeUnifiable(shape);
    }
}

}  // namespace ksys::snd
