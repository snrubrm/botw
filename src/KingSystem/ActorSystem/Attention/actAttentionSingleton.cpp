#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(Attention)

bool Attention::sub_7100D753B0() const {
    return (mFlagsE22.isOn(2) || (mFlagsE21 & 8)) && !mEnabled;
}

bool Attention::sub_7100D74114() const {
    if (!mEnabled)
        return false;
    const auto& lock = mLists[1];
    if (lock.mCount == 0)
        return false;
    return *lock.mEntries != nullptr;
}

bool Attention::sub_7100D742E8(s32 list) const {
    return mLists[list].mCount == 0;
}

// NON_MATCHING: the original tail-calls BaseProcLink::operator= (and stores the flag byte before the call)
void Attention::sub_7100D744B8(const BaseProcLink& link) {
    if (!link.hasProc())
        return;
    mFlagsE21 |= 4;
    mRequestedTarget = link;
}

void Attention::setPauseState(bool paused) {
    mFlagsE22.changeBit(0, paused);
}

}  // namespace ksys::act
