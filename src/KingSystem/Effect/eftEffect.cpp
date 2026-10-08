#include "KingSystem/Effect/eftEffect.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>

namespace ksys::eft {

SEAD_SINGLETON_DISPOSER_IMPL(Effect)

void Unk_EffectActorTable::sub_7100DA2118() {
    // NON_MATCHING: SDK range iteration uses a different counter instead of the native paired loop.
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mCount = 0;
    for (auto& entry : _0) {
        entry.actor = nullptr;
        entry._28 = false;
    }
}

bool Unk_EffectActorTable::sub_7100DA2330(act::Actor* actor) {
    // NON_MATCHING: iterator addressing/unrolling and the saturating decrement differ.
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto& entry : _0) {
        if (entry.actor == actor) {
            entry.actor = nullptr;
            mCount = sead::Mathi::max(mCount - 1, 0);
            return true;
        }
    }
    return false;
}

}  // namespace ksys::eft
