#include "aal/aalGroup.h"
#include <basis/seadNew.h>
#include "aal/aalGroupLimiter.h"
#include "aal/aalSoundSource.h"
#include "aal/aalTimedFader.h"

namespace aal {

// NON_MATCHING: the zero stores of the counters (0x150..0x160) and of the two trailing pointers are emitted in the opposite order
// 0x7100b7f748
Group::Group()
    : sead::TTreeNode<Group*>(this), mInitialized(false), mDucker(nullptr), _98(nullptr), mAggregatedParam(nullptr),
      mParamBuffer(nullptr), mDuckingVolume(1.0f), mDuckingVolumeFloor(0.0f), mDuckingMode(1),
      _13c(0), mHasDefaultParam(true), mLimiter(nullptr) {
    mDuckingCount = 0;
    _154 = 0;
    _158 = 0;
    _15c = 0;
    mNumSounds = 0;
}

// 0x7100b7f860 (D1) / 0x7100b7f9a8 (D0), and their thunks for the second base
Group::~Group() {
    finalize();
}

// 0x7100b7fa50
void Group::initialize(const sead::SafeString& name, sead::Heap* heap) {
    if (mInitialized)
        return;

    setObjName(name);
    mParamBuffer = new (heap, 0x20) u8[sizeof(SoundParam)];
    mAggregatedParam = new (mParamBuffer) SoundParam;
    mDucker = new (heap) GroupDucker(this);
    mLimiter = new (heap) GroupLimiter;
    mLimiter->initialize(this, heap);
    mHasDefaultParam = !SoundParam::isInitial(mDefaultParam);
    mInitialized = true;
}

// 0x7100b7fb18
void Group::finalize() {
    if (!mInitialized)
        return;

    if (mDucker) {
        mDucker->finalize();
        delete mDucker;
        mDucker = nullptr;
    }
    if (mParamBuffer) {
        delete static_cast<u8*>(mParamBuffer);
        mParamBuffer = nullptr;
    }
    mAggregatedParam = nullptr;
    if (mLimiter) {
        mLimiter->finalize();
        delete mLimiter;
        mLimiter = nullptr;
    }
    mInitialized = false;
}

// 0x7100b7fcc8
void Group::setDefaultParam(const SoundParam& param) {
    SoundParam::copy(&mDefaultParam, param);
    mHasDefaultParam = !SoundParam::isInitial(mDefaultParam);
}

// 0x7100b7fd54
void Group::calcParam_() {
    mNumSounds = mDuckingCount + _158 + _15c;
    if (mNumSounds != 0) {
        if (mHasDefaultParam) {
            SoundParam::aggregate(mAggregatedParam, mDefaultParam, mCurrentParam);
            if (Group* parent = getParent())
                SoundParam::aggregate(mAggregatedParam, *parent->mAggregatedParam);
        } else {
            if (Group* parent = getParent())
                SoundParam::aggregate(mAggregatedParam, *parent->mAggregatedParam, mCurrentParam);
            else
                SoundParam::copy(mAggregatedParam, mCurrentParam);
        }
        calcSilence_();
    }
}
// 0x7100b7fb9c
s32 Group::calcTreeDepth() const {
    s32 depth = -1;
    const sead::TTreeNode<Group*>* node = &treeNode();
    do {
        node = node->parent();
        ++depth;
    } while (node);
    return depth;
}

// 0x7100b7fc18
Group* Group::getParent() const {
    if (auto* parent = treeNode().parent())
        return parent->value();
    return nullptr;
}

// 0x7100b7fbb4
void Group::calcActiveSoundLimit() {
    mLimiter->calcActiveSoundLimit();
}

// 0x7100b7fbbc
void Group::calcRequestSoundLimit() {
    mLimiter->calcRequestSoundLimit();
}

// 0x7100b7fd04
void Group::invalidateORNode() {}

// 0x7100b7fd0c
void Group::setDuckingVolumeFloor(f32 floor) {
    if (floor >= 0.0f && floor <= 1.0f)
        mDuckingVolumeFloor = floor;
}

// 0x7100b7fd28
void Group::calcInit_() {
    mLimiter->calc();
    mNumSounds = 0;
    mDuckingCount = 0;
    _154 = 0;
    _158 = 0;
    _15c = 0;
}

// 0x7100b7fe0c
void Group::calcDucker_() {
    if (mDucker)
        mDucker->calc();
}

// 0x7100b7fe1c
void Group::aggregateDuckingVolumeFromDucker_(f32 volume) {
    if (mDuckingMode == 0)
        mDuckingVolume *= volume;
    else if (mDuckingMode == 1)
        mDuckingVolume = mDuckingVolume < volume ? mDuckingVolume : volume;
}

// 0x7100b80070
bool Group::isOnDucking() const {
    return mDuckingCount > 0;
}

// 0x7100b80080
const sead::SafeString& Group::getDuckingSourceName() const {
    return mName;
}

// 0x7100b80088
void Group::calcSilence_() {}

// 0x7100b82590

// 0x7100b8259c

// 0x7100b825c0

// 0x7100b825ec

// 0x7100b82848 .. 0x7100b82868: SoundGroup has no children

// 0x7100b82ae0 / 0x7100b82ae8

// 0x7100b7fbc4
void Group::calcNumSounds() {
    if (Group* parent = getParent()) {
        const s32 n0 = mDuckingCount;
        const s32 n1 = _154;
        const s32 n2 = _158;
        const s32 n3 = _15c;
        parent->mDuckingCount += n0;
        parent->_154 += n1;
        parent->_158 += n2;
        parent->_15c += n3;
    }
}

// 0x7100b7fc30
void Group::pushDescendantGroupArray(sead::PtrArray<Group>* groups) {
    if (groups) {
        for (auto* node = treeNode().child(); node; node = node->next())
            node->value()->pushDescendantGroupArrayChild_(groups);
    }
}

// 0x7100b7fc6c
void Group::pushDescendantGroupArrayChild_(sead::PtrArray<Group>* groups) {
    groups->pushBack(this);
    for (auto* node = treeNode().child(); node; node = node->next())
        node->value()->pushDescendantGroupArrayChild_(groups);
}

// 0x7100b7fe4c
void Group::calcDuckingVolume_() {
    if (mNumSounds != 0) {
        if (Group* parent = getParent()) {
            if (mDuckingMode == 0) {
                mDuckingVolume = parent->mDuckingVolume * mDuckingVolume;
            } else if (mDuckingMode == 1) {
                const f32 own = mDuckingVolume;
                const f32 parent_volume = parent->mDuckingVolume;
                mDuckingVolume = own < parent_volume ? own : parent_volume;
            }
        }
        mDuckingVolume = mDuckingVolume < mDuckingVolumeFloor ? mDuckingVolumeFloor : mDuckingVolume;
    }
}

// 0x7100b826bc

// 0x7100b8286c

// 0x7100b828b4

// 0x7100b828e0

}  // namespace aal
