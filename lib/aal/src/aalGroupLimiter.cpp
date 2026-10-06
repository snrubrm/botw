#include "aal/aalGroupLimiter.h"
#include "aal/aalGroup.h"
#include "aal/aalGroupMgr.h"
#include "aal/aalRequestIntervalLimiter.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b800ac
GroupLimiter::GroupLimiter()
    : mInitialized(false), mGroup(nullptr), mActiveSoundLimiter(nullptr),
      mRequestSoundLimiter(nullptr), mRequestIntervalLimiter(nullptr),
      mActiveSoundLimitList(nullptr), mRequestSoundLimitList(nullptr),
      mUpperActiveSoundLimitList(nullptr), mUpperRequestSoundLimitList(nullptr),
      mRequestIntervalLimiterForLimit(nullptr), _58(), _60(-1), _64(0), _68(-1), _6c(0), _70(0),
      _74(1.0f), _78(1.0f), _7c(0), _80(0) {}

// 0x7100b80128
void GroupLimiter::finalize() {
    mInitialized = false;
}

// 0x7100b80134
void GroupLimiter::initialize(Group* group, sead::Heap* heap) {
    if (!mInitialized) {
        mGroup = group;
        mInitialized = true;
    }
}

// 0x7100b8014c
void GroupLimiter::calc() {
    if (mRequestIntervalLimiter)
        mRequestIntervalLimiter->calc();
}

// 0x7100b8015c
bool GroupLimiter::limitRequestInterval(SoundSource* source) {
    if (mRequestIntervalLimiterForLimit)
        return mRequestIntervalLimiterForLimit->limit(source);
    return true;
}

// 0x7100b80110 / 0x7100b80130
GroupLimiter::~GroupLimiter() {
    mInitialized = false;
}

// 0x7100b8029c
void GroupLimiter::updateUpperActiveSoundLimitList() {
    mUpperActiveSoundLimitList = nullptr;
    for (Group* group = mGroup->getParent(); group; group = group->getParent()) {
        if (auto* list = group->mLimiter->mActiveSoundLimitList) {
            mUpperActiveSoundLimitList = list;
            break;
        }
    }
}

// 0x7100b802d8
void GroupLimiter::updateUpperRequestSoundLimitList() {
    mUpperRequestSoundLimitList = nullptr;
    for (Group* group = mGroup->getParent(); group; group = group->getParent()) {
        if (auto* list = group->mLimiter->mRequestSoundLimitList) {
            mUpperRequestSoundLimitList = list;
            break;
        }
    }
}

// 0x7100b80314: the outermost group with a limiter wins
void GroupLimiter::updateUsingRequestIntervalLimiter() {
    mRequestIntervalLimiterForLimit = nullptr;
    for (Group* group = mGroup; group; group = group->getParent()) {
        if (auto* limiter = group->mLimiter->mRequestIntervalLimiter)
            mRequestIntervalLimiterForLimit = limiter;
    }
}

// 0x7100b80460
void GroupLimiter::setActiveSoundLimiter(ActiveSoundLimiter* limiter, sead::OffsetList<SoundSource>* sources) {
    mActiveSoundLimiter = limiter;
    mActiveSoundLimitList = sources;
    SystemAccessor::getGroupMgr()->updateActiveSoundLimiterStructure();
}

// 0x7100b8047c
void GroupLimiter::setRequestSoundLimiter(RequestSoundLimiter* limiter, sead::OffsetList<SoundSource>* sources) {
    mRequestSoundLimiter = limiter;
    mRequestSoundLimitList = sources;
    SystemAccessor::getGroupMgr()->updateRequestSoundLimiterStructure();
}

// 0x7100b80498
void GroupLimiter::setRequestIntervalLimiter(RequestIntervalLimiter* limiter) {
    mRequestIntervalLimiter = limiter;
    SystemAccessor::getGroupMgr()->updateRequestIntervalLimiterStructure();
}

}  // namespace aal

namespace aal {

// 0x7100b82af0
GroupDucker::GroupDucker(IDuckingSource* source)
    : mInitialized(false), mSettings(), mState(0), mSource(source), _40(0), _44(0) {
    mTargets.initOffset(0x40);
    if (source)
        source->getDuckingSourceName();
}

// 0x7100b82b4c (D1) / 0x7100b82b6c (D0)
GroupDucker::~GroupDucker() {
    mInitialized = false;
}

// 0x7100b82b70
void GroupDucker::initialize(sead::Heap*) {
    if (!mInitialized) {
        _40 = 0;
        _44 = 0;
        mState = 0;
        mInitialized = true;
    }
}

// 0x7100b82b64
void GroupDucker::finalize() {
    mInitialized = false;
}

// 0x7100b82b8c
void GroupDucker::setup(const Settings& settings) {
    mSettings = settings;
}

// 0x7100b83050
void GroupDucker::suspend() {
    mState = 6;
}

// 0x7100b8305c
void GroupDucker::resetState() {
    mState = 0;
}

}  // namespace aal

namespace aal {

// 0x7100b8320c
bool GroupDucker::Target::isFaderMoving() const {
    return mFader.getValue() != mFader.getNextValue();
}

// 0x7100b832c0
f32 GroupDucker::Target::getFaderVolume() const {
    return mFader.getValue();
}

}  // namespace aal
