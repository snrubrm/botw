#include "aal/aalGroupLimiter.h"
#include "aal/aalGroup.h"
#include "aal/aalGroupMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

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

// 0x7100b80314
void GroupLimiter::updateUsingRequestIntervalLimiter() {
    mRequestIntervalLimiterForLimit = nullptr;
    for (Group* group = mGroup; group; group = group->getParent()) {
        if (auto* limiter = group->mLimiter->mRequestIntervalLimiter) {
            mRequestIntervalLimiterForLimit = limiter;
            break;
        }
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
