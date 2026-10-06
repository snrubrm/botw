#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include <basis/seadNew.h>
#include <nn/os.h>
#include <prim/seadScopedLock.h>
#include "aal/aalInterior.h"
#include "aal/aalInteriorSet.h"
#include "aal/aalListenerMgr.h"
#include "aal/aalOutputDevice.h"
#include "aal/aalSettings.h"
#include "aal/aalSpeakerBalanceUnifier.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

namespace {
const SpeakerBalanceUnifierMgr::Quad sDefaultRatios = {{0.1f, 0.3f, 0.3f, 0.75f}};
}  // namespace

// 0x7100b93f40
SpeakerBalanceUnifierMgr::SpeakerBalanceUnifierMgr()
    : mInitialized(false), mTable(nullptr),
      mRegisterCullingDistance(0.0f), _50(0xff), _98(false), _9c{780.0f, 40.0f},
      _a4(sDefaultRatios), _b4(0), mCalcBeginTick(nn::os::GetSystemTick().value),
      mCalcTicks(0), _100(0x4b7e502b) {
    mActiveUnifiers.initOffset(offsetof(SpeakerBalanceUnifier, mListNode));
    mInteriorSizes = nullptr;
    _b4 |= 1;
}

// 0x7100b94040
SpeakerBalanceUnifierMgr::~SpeakerBalanceUnifierMgr() {
    finalize();
}

// 0x7100b94150
void SpeakerBalanceUnifierMgr::initialize(const InitializeArg& arg, sead::Heap* heap) {
    if (mInitialized)
        return;

    Settings* settings = SystemAccessor::getSettings();
    if (!settings)
        return;

    if (OutputDevice* device = settings->getOutputDevice(DeviceType::TV)) {
        const s32 num = device->getNumOfInteriorMax();
        mInteriorSizes = new (heap, 8) f32[num];
        mInteriorNum = num;
        for (s32 i = 0; i < mInteriorNum; ++i)
            mInteriorSizes[i] = 1.0f;
    }

    mTable = new (heap, 8) UnifierSpeakerBalanceTable;
    mTable->initialize(heap);
    setupInteriorSize();

    mUnifiers.allocBuffer(arg.unifier_num, heap, 8);
    for (s32 i = 0; i < mUnifiers.capacity(); ++i) {
        auto* unifier = new (heap, 8) SpeakerBalanceUnifier;
        unifier->initialize(SystemAccessor::getListenerMgr()->getListenerNum(), heap);
        mUnifiers.pushBack(unifier);
    }

    mActiveUnifiers.clear();
    _50 = 0xff;
    mName.clear();
    mInitialized = true;
}

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

// 0x7100b942f0
void SpeakerBalanceUnifierMgr::setupInteriorSize() {
    Settings* settings = SystemAccessor::getSettings();
    if (!settings)
        return;

    if (OutputDevice* device = settings->getOutputDevice(DeviceType::TV)) {
        if (InteriorSet* interior_set = device->getCurrentInteriorSet()) {
            const s32 num = interior_set->getNumOfInterior();
            for (s32 i = 0; i < num; ++i) {
                Interior* interior = interior_set->getInterior(i);
                mInteriorSizes[i] = interior ? interior->getInteriorSizeAsInGameLength() : 1.0f;
            }
        } else {
            for (s32 i = 0; i < mInteriorNum; ++i)
                mInteriorSizes[i] = 1.0f;
        }
    } else {
        for (s32 i = 0; i < mInteriorNum; ++i)
            mInteriorSizes[i] = 1.0f;
    }
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
