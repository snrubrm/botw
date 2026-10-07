#include "aal/aalGroupLimiter.h"
#include <basis/seadNew.h>
#include "aal/aalActiveSoundLimiter.h"
#include "aal/aalGroup.h"
#include "aal/aalGroupMgr.h"
#include "aal/aalRequestIntervalLimiter.h"
#include "aal/aalRequestSoundLimiter.h"
#include "aal/aalSettings.h"
#include "aal/aalSoundSource.h"
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

// 0x7100b80170
void GroupLimiter::calcActiveSoundLimit() {
    if (!mActiveSoundLimiter || !mActiveSoundLimitList)
        return;

    mActiveSoundLimiter->mVirtualizedBy = SoundSource::VirtualizedBy::GroupLimiter;
    mActiveSoundLimiter->calcLimit(mActiveSoundLimitList);

    for (SoundSource& source : mActiveSoundLimitList->robustRange()) {
        mActiveSoundLimitList->erase(&source);
        if (source.mState != 7) {
            if (!mUpperActiveSoundLimitList ||
                source.isVirtualized(SoundSource::VirtualizedBy(mActiveSoundLimiter->mVirtualizedBy))) {
                if (source.mSoundGroup)
                    source.mSoundGroup->addToPlayingSoundSources(&source);
            } else {
                mUpperActiveSoundLimitList->pushBack(&source);
            }
        }
    }
}

// 0x7100b80274
void GroupLimiter::calcRequestSoundLimit() {
    if (mRequestSoundLimiter && mRequestSoundLimitList)
        mRequestSoundLimiter->calcLimit(mRequestSoundLimitList, mUpperRequestSoundLimitList);
}

// 0x7100b80354
bool GroupLimiter::addToActiveSoundLimitList(sead::OffsetList<SoundSource>* sources) {
    if (!sources)
        return false;

    sead::OffsetList<SoundSource>* list = mActiveSoundLimitList;
    if (!list)
        list = mUpperActiveSoundLimitList;
    if (!list)
        return false;

    for (SoundSource& source : sources->robustRange()) {
        sources->erase(&source);
        list->pushBack(&source);
    }
    return true;
}

// 0x7100b8040c
bool GroupLimiter::addToActiveSoundLimitList(SoundSource* source) {
    if (!source)
        return false;

    sead::OffsetList<SoundSource>* list = mRequestSoundLimitList;
    if (!list)
        list = mUpperRequestSoundLimitList;
    if (!list)
        return false;

    list->pushBack(source);
    return true;
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
    : mInitialized(false), mSettings(), mState(0), mSource(source), _40(0.0f), _44(0.0f) {
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
        _40 = 0.0f;
        _44 = 0.0f;
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

// 0x7100b82ba0
void GroupDucker::calc() {
    if (mTargets.size() == 0)
        return;

    updateStartEnd_();
    updateState_();
    if (mState != 0) {
        for (Target& target : mTargets) {
            target.mFader.calc();
            if (target.mGroup)
                target.mGroup->aggregateDuckingVolumeFromDucker_(target.mFader.getValue());
        }
        if (aal::Settings* settings = SystemAccessor::getSettings()) {
            _40 += settings->mCalcTimeStep;
            _44 += settings->mCalcTimeStep;
        }
    } else {
        _40 = 0.0f;
        _44 = 0.0f;
    }
}

// NON_MATCHING: same code; the load of the ducking source is hoisted in front of the state test here.
// 0x7100b82c64
void GroupDucker::updateStartEnd_() {
    if (static_cast<u32>(mState) > 4)
        return;

    if ((1 << mState) & 0x19) {
        // Not ducking (0), or ending (3, 4): start if the ducking source ducks.
        if (!mSource || !mSource->isOnDucking())
            return;
        if (mSettings._0 == 0.0f) {
            for (Target& target : mTargets) {
                target.mFader.setCurveType(FadeCurveType(target.mSettings._c));
                target.mFader.moveTo(target.mSettings._0, target.mSettings._4);
            }
            mState = 2;
        } else {
            mState = 1;
        }
        _40 = 0.0f;
        return;
    }

    // Waiting to start (1) or ducking (2).
    if (mSource && mSource->isOnDucking()) {
        if (mSettings._8 > 0.0f && _44 >= mSettings._8) {
            for (Target& target : mTargets) {
                target.mFader.setCurveType(FadeCurveType(target.mSettings._c));
                target.mFader.moveTo(1.0f, target.mSettings._8);
            }
            mState = 5;
        }
        return;
    }

    if (mSettings._4 == 0.0f) {
        for (Target& target : mTargets) {
            target.mFader.setCurveType(FadeCurveType(target.mSettings._c));
            target.mFader.moveTo(1.0f, target.mSettings._8);
        }
        mState = 4;
    } else {
        mState = 3;
    }
    _40 = 0.0f;
}

// 0x7100b82e30
void GroupDucker::updateState_() {
    switch (mState) {
    case 1:
        if (!(_40 >= mSettings._0))
            return;
        for (Target& target : mTargets) {
            target.mFader.setCurveType(FadeCurveType(target.mSettings._c));
            target.mFader.moveTo(target.mSettings._0, target.mSettings._4);
        }
        mState = 2;
        break;
    case 3:
        if (!(_40 >= mSettings._4))
            return;
        for (Target& target : mTargets) {
            target.mFader.setCurveType(FadeCurveType(target.mSettings._c));
            target.mFader.moveTo(1.0f, target.mSettings._8);
        }
        mState = 4;
        break;
    case 4:
        for (Target& target : mTargets) {
            if (target.mFader.getValue() != target.mFader.getNextValue())
                return;
        }
        mState = 0;
        break;
    case 5:
        for (Target& target : mTargets) {
            if (target.mFader.getValue() != target.mFader.getNextValue())
                return;
        }
        if (mSource && mSource->isOnDucking())
            return;
        mState = 0;
        break;
    case 6:
        for (Target& target : mTargets) {
            target.mFader.setValueImmediate(1.0f);
            if (target.mGroup)
                target.mGroup->aggregateDuckingVolumeFromDucker_(target.mFader.getValue());
        }
        mState = 0;
        break;
    default:
        break;
    }
}

// 0x7100b83050
void GroupDucker::suspend() {
    mState = 6;
}

// 0x7100b8305c
void GroupDucker::resetState() {
    mState = 0;
}

// NON_MATCHING: the original compares the pointer of the ducking source with the group without the pointer adjustment of
// the base class (Group -> IDuckingSource).
// 0x7100b83064
bool GroupDucker::createAndAddTarget(Group* group, const TargetSettings& settings, sead::Heap* heap) {
    if (!group)
        return false;
    for (Target& target : mTargets) {
        if (target.mGroup == group)
            return false;
    }
    if (mSource == group)
        return false;

    Target* target = new (heap) Target;
    if (!target)
        return false;
    target->mGroup = group;
    target->mSettings._0 = settings._0;
    target->mSettings._4 = settings._4;
    target->mSettings._8 = settings._8;
    target->mSettings._c = settings._c;
    target->mFader.setCurveType(FadeCurveType(settings._c));
    target->mFader.setValueImmediate(1.0f);
    if (!mTargets.isNodeLinked(target))
        mTargets.pushBack(target);
    return true;
}

// NON_MATCHING: the original calls the other overload as a tail call; this one converts the returned bool.
// 0x7100b831a0
bool GroupDucker::createAndAddTarget(const sead::SafeString& group_name, const TargetSettings& settings,
                                     sead::Heap* heap) {
    if (GroupMgr* mgr = SystemAccessor::getGroupMgr()) {
        if (Group* group = mgr->findGroup(group_name))
            return createAndAddTarget(group, settings, heap);
    }
    return false;
}

// 0x7100b8321c
void GroupDucker::removeAndDestroyAllTargets() {
    if (mTargets.isEmpty())
        return;

    for (Target& target : mTargets.robustRange()) {
        if (mTargets.indexOf(&target) >= 0)
            mTargets.erase(&target);
        delete &target;
    }
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
