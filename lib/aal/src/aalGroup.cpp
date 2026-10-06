#include "aal/aalGroup.h"
#include "aal/aalGroupLimiter.h"
#include "aal/aalTimedFader.h"

namespace aal {

// 0x7100b7fb9c
s32 Group::calcTreeDepth() const {
    s32 depth = -1;
    const sead::TTreeNode<Group*>* node = &mTreeNode;
    do {
        node = node->parent();
        ++depth;
    } while (node);
    return depth;
}

// 0x7100b7fc18
Group* Group::getParent() const {
    if (auto* parent = mTreeNode.parent())
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
void SoundGroup::allowEmit(bool allow) {
    mEmitFlags.setDirect(allow ? 0xff : 0);
}

// 0x7100b8259c
void SoundGroup::allowEmit(sead::BitFlag8 flags, bool allow) {
    if (allow)
        mEmitFlags.set(flags);
    else
        mEmitFlags.reset(flags);
}

// 0x7100b825c0
void SoundGroup::silence(bool silence, f32 fade_time) {
    if (fade_time >= 0.0f && mSilenceFader) {
        if (silence)
            mSilenceFader->moveTo(0.0f, fade_time);
        else
            mSilenceFader->moveTo(1.0f, fade_time);
    }
}

// 0x7100b825ec
void SoundGroup::setReleaseTime(f32 release_time) {
    if (release_time >= 0.0f)
        mReleaseTime = release_time;
}

// 0x7100b82848 .. 0x7100b82868: SoundGroup has no children
bool SoundGroup::pushFrontChild_(Group* child) {
    return false;
}

bool SoundGroup::pushBackChild_(Group* child) {
    return false;
}

bool SoundGroup::insertBeforeChild_(Group* child, Group* before) {
    return false;
}

bool SoundGroup::insertAfterChild_(Group* child, Group* after) {
    return false;
}

void SoundGroup::removeChild_(Group* child) {}

// 0x7100b82ae0 / 0x7100b82ae8
bool SoundGroup::isSoundGroup() const {
    return true;
}

bool SoundGroup::isGroupFolder() const {
    return false;
}

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
        for (auto* node = mTreeNode.child(); node; node = node->next())
            node->value()->pushDescendantGroupArrayChild_(groups);
    }
}

// 0x7100b7fc6c
void Group::pushDescendantGroupArrayChild_(sead::PtrArray<Group>* groups) {
    groups->pushBack(this);
    for (auto* node = mTreeNode.child(); node; node = node->next())
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

}  // namespace aal
