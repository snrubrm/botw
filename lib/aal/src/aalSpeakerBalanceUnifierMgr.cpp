#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include <nn/os.h>
#include <prim/seadScopedLock.h>
#include "aal/aalSpeakerBalanceUnifier.h"

namespace aal {

// 0x7100b94074
void SpeakerBalanceUnifierMgr::finalize() {
    if (!mInitialized)
        return;

    mActiveUnifiers.clear();
    if (mUnifiers.isBufferReady()) {
        for (s32 i = 0; i < mUnifiers.size(); ++i) {
            mUnifiers[i]->finalize();
            delete mUnifiers[i];
        }
        mUnifiers.freeBuffer();
    }

    if (mTable) {
        delete mTable;
        mTable = nullptr;
    }
    if (mInteriorSizes) {
        delete mInteriorSizes;
        mInteriorSizes = nullptr;
    }
    mInitialized = false;
}

// 0x7100b943e4
void SpeakerBalanceUnifierMgr::calc() {
    if (!mInitialized)
        return;

    mCalcBeginTick = nn::os::GetSystemTick().value;
    for (SpeakerBalanceUnifier& unifier : mActiveUnifiers)
        unifier.calc();
    mCalcTicks = nn::os::GetSystemTick().value - mCalcBeginTick;
}

// 0x7100b9446c
void SpeakerBalanceUnifierMgr::setupUnifierSpeakerBalanceTable() {
    if (mTable)
        mTable->makeTable();
}

// 0x7100b9447c
void SpeakerBalanceUnifierMgr::setRegisterCullingDistance(f32 distance) {
    mRegisterCullingDistance = distance;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (SpeakerBalanceUnifier& unifier : mActiveUnifiers)
        unifier.setRegisterCullingDistance(distance);
}

// 0x7100b94508
SpeakerBalanceUnifier*
SpeakerBalanceUnifierMgr::allocSpeakerBalanceUnifier(const sead::SafeString& name, sead::Heap* heap) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mUnifiers.size(); ++i) {
        SpeakerBalanceUnifier* unifier = mUnifiers[i];
        if (!unifier->mAllocated) {
            unifier->execOnAllocated(name, heap);
            unifier->setRegisterCullingDistance(mRegisterCullingDistance);
            mActiveUnifiers.pushBack(unifier);
            return unifier;
        }
    }
    return nullptr;
}

// 0x7100b945dc
void SpeakerBalanceUnifierMgr::freeSpeakerBalanceUnifier(SpeakerBalanceUnifier* unifier) {
    if (!unifier)
        return;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (mActiveUnifiers.isNodeLinked(unifier))
        mActiveUnifiers.erase(unifier);
    unifier->execOnFree();
}

}  // namespace aal
