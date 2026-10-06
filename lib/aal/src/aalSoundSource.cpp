#include "aal/aalSoundSource.h"
#include "aal/aalSpatialPlayingParamPool.h"
#include <math/seadMathCalcCommon.h>
#include "aal/aalEmitter.h"
#include "aal/aalArbiter.h"
#include "aal/aalGroup.h"
#include "aal/aalISpeakerBalanceSupplier.h"
#include "aal/aalMarkerController.h"
#include "aal/aalSoundSourceUnifier.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b76808
SoundSource::SoundSource()
    : _8(0), mState(0), mId(0), mPrepareFlags(0), mPauseFlags(0), mVirtualizedBy(0), mPlayingTime(0.0f),
      _1c(-1), _20(0), mStartSamplePos(0), mStartDelayTime(0.0f), mFadeInTime(0.0f), mFadeCurveType(),
      mDefaultParam(), mParam(), mAggregatedParam(nullptr), mAggregatedParamBuffer(nullptr),
      mInteriorNum(0), mTrackNum(0), mChannelNum(), mPriority(1.0f), _d8(1.0f), mPriorityScale(1.0f),
      mSoundGroup(nullptr), mEmitter(nullptr), mSpeakerBalanceSupplier(nullptr),
      mPlayingStateController(nullptr), mFader(nullptr), mSpatialSetting(), mSpatialCalculator(nullptr),
      mSpatialPlayingParam(nullptr), mUnifierSource(nullptr), mMarkerController(nullptr), mArbiterNode(), _1d0(),
      mEmitterNode() {}

// 0x7100b768a0 (D1) / 0x7100b76964 (D0)
SoundSource::~SoundSource() {
    finalize();
}

// 0x7100b768d4
void SoundSource::finalize() {
    if (!_8)
        return;

    reset();
    if (mPlayingStateController) {
        mPlayingStateController->finalize();
        delete mPlayingStateController;
        mPlayingStateController = nullptr;
    }
    if (mFader) {
        delete mFader;
        mFader = nullptr;
    }
    if (mAggregatedParamBuffer) {
        delete mAggregatedParamBuffer;
        mAggregatedParamBuffer = nullptr;
    }
    mAggregatedParam = nullptr;
    if (mMarkerController) {
        delete mMarkerController;
        mMarkerController = nullptr;
    }
    _8 = 0;
}

// 0x7100b76a68
void SoundSource::reset() {
    freeUnifierSource_();
    finishNow_();
    freeUnifierSource_();

    mPauseFlags = sead::BitFlag8(0);
    mVirtualizedBy = 0;
    mPrepareFlags = 1;
    mPlayingTime = 0.0f;
    mDefaultParam.reset();
    mParam.reset();
    mAggregatedParam->reset();
    mDefaultParam.setDeviceVolume(DeviceType(0), 1.0f);
    mDefaultParam.setBusVolume(BusType(0), 1.0f);
    mTrackNum = 0;
    mInteriorNum = 0;
    for (u8& channel_num : mChannelNum)
        channel_num = 0;
    mPriority = 1.0f;
    _d8 = 1.0f;
    mPriorityScale = 1.0f;
    mStartDelayTime = 0.0f;
    mFadeInTime = 0.0f;
    mFadeCurveType = FadeCurveType();
    for (u8& track_volume : mTrackVolume)
        track_volume = 0xff;
    if (mPlayingStateController)
        mPlayingStateController->reset();
    if (mFader)
        mFader->setValueImmediate(1.0f);
    detachSoundGroup();
    if (mEmitter) {
        if (mEmitterNode.isLinked())
            mEmitter->removeSoundSource(this);
        mEmitter = nullptr;
    }
    mSpeakerBalanceSupplier = nullptr;
    if (mSpatialCalculator) {
        SystemAccessor::getArbiter()->getSpatialCalculatorPool()->free(mSpatialCalculator);
        mSpatialCalculator = nullptr;
    }
    if (mSpatialPlayingParam) {
        SystemAccessor::getArbiter()->getSpatialPlayingParamPool()->free(mSpatialPlayingParam);
        mSpatialPlayingParam = nullptr;
    }
    mSpatialSetting.reset();
    if (mMarkerController)
        mMarkerController->reset();
    _1c = -1;
    _20 = 0;
    mStartSamplePos = 0;
    mState = 0;
}

// 0x7100b769a0
void SoundSource::initialize(sead::Heap* heap) {
    if (_8)
        return;

    mPlayingStateController = new (heap, 8) PlayingStateController;
    if (mPlayingStateController)
        mPlayingStateController->initialize(heap);
    mAggregatedParamBuffer = new (heap, 0x20) u8[sizeof(SoundParam)];
    mAggregatedParam = new (mAggregatedParamBuffer) SoundParam;
    mFader = new (heap, 8) SimpleTimedFader(1.0f);
    mMarkerController = new (heap, 8) MarkerController;
    reset();
    _8 = 1;
}

// 0x7100b77d6c
void SoundSource::pause(bool pause, f32 fade_time) {
    this->pause(sead::BitFlag8(0xff), pause, fade_time);
}

// 0x7100b77e8c
bool SoundSource::setStartDelayTime(f32 delay_time) {
    const s32 state = mState;
    bool result = false;
    if (delay_time >= 0.0f && state <= 2) {
        mStartDelayTime = delay_time;
        mState = delay_time > 0.0f ? 1 : 2;
        result = true;
    }
    return result;
}

// 0x7100b77ec4
bool SoundSource::setFadeInTime(f32 fade_in_time) {
    const s32 state = mState;
    bool result = false;
    if (fade_in_time >= 0.0f && state <= 2) {
        mFadeInTime = fade_in_time;
        result = true;
    }
    return result;
}

// 0x7100b77e5c
void SoundSource::startPrepared() {
    mPlayingStateController->mSoundController->startPrepared();
    mState = 4;
}

// 0x7100b781fc
Handle SoundSource::getUnifiedSoundHandle() const {
    if (mUnifierSource)
        return mUnifierSource->getTargetHandle();
    return Handle::cInvalid;
}

// NON_MATCHING: same checks and calls; the original does not shrink-wrap the frame setup around the state test.
// 0x7100b78228
u32 SoundSource::getPlaySamplePosition() const {
    if (mState == 0 || mState == 7)
        return 0;
    if (mState != 8)
        return mPlayingStateController->getPlayingSamplePos();

    Handle handle = getUnifiedSoundHandle();
    if (const SoundSource* sound_source = handle.getSoundSource())
        return sound_source->getPlaySamplePosition();
    return 0;
}

// 0x7100b781a4
void SoundSource::setPriority(f32 priority) {
    if (priority >= 0.0f && priority <= 1.0f)
        mPriority = priority;
}

// 0x7100b783b8
f32 SoundSource::getFadeInTimeIfBeforePlaying() const {
    if (mState <= 2)
        return mFadeInTime;
    return -1.0f;
}

// 0x7100b78094
bool SoundSource::setStreamRegionCallback(SoundController::StreamRegionCallback callback,
                                          void* user_data) {
    if (mState <= 2) {
        mPlayingStateController->mSoundController->setStreamRegionCallback(callback, user_data);
        return true;
    }
    return false;
}

// 0x7100b780c8
void SoundSource::setIgnorePrefetch(bool ignore) {
    if (mState <= 2)
        mPlayingStateController->mSoundController->setIgnorePrefetch(ignore);
}

// 0x7100b78048
bool SoundSource::setStartSamplePos(s32 position) {
    const s32 state = mState;
    bool result = false;
    if (position >= 0 && state <= 2) {
        mStartSamplePos = position;
        mPlayingStateController->mSoundController->setStartSampleOffset(position);
        result = true;
    }
    return result;
}

// 0x7100b78084
const AssetInfo* SoundSource::getAssetInfo() const {
    return mPlayingStateController->mSoundController->mAssetInfo;
}

// 0x7100b78524
void SoundSource::aggregateAndClampParams_() {
    SoundParam::aggregate(mAggregatedParam, mDefaultParam, mParam);
    if (mEmitter) {
        SoundParam::aggregate(mAggregatedParam, mEmitter->mSoundParam);
        if (mEmitter->isDebugMuted())
            mAggregatedParam->setVolume(0.0f);
    }
    if (mSoundGroup)
        SoundParam::aggregate(mAggregatedParam, *mSoundGroup->getAggregatedParam());
    mAggregatedParam->clampExceptVolume();
    mAggregatedParam->clampMinBusVolume();
}

// NON_MATCHING: same loads and calls; the original sets up the frame at the start and keeps branches where this uses a conditional select.
// 0x7100b782a4
const char* SoundSource::getAssetName() const {
    if (const AssetInfo* info = getAssetInfo())
        return info->getAssetName();
    return nullptr;
}

// 0x7100b78310
bool SoundSource::isLooped() const {
    if (auto* info = mPlayingStateController->mSoundController->mAssetInfo)
        return info->mFlags & 1;
    return false;
}

// 0x7100b78178
f32 SoundSource::getTrackVolume(s32 track) const {
    if (static_cast<u32>(track) <= 7)
        return mTrackVolume[track] * (1.0f / 255.0f);
    return 0.0f;
}

// 0x7100b77eec
bool SoundSource::setReleaseCurveType(FadeCurveType type) {
    if (mState <= 2) {
        mPlayingStateController->mSoundController->setFadeCurveType(type);
        return true;
    }
    return false;
}

// 0x7100b781c0
bool SoundSource::isVirtualized() const {
    return mVirtualizedBy != 0;
}

// 0x7100b77ca0
void SoundSource::kill() {
    reset();
}

inline void SoundSource::freeUnifierSource_() {
    if (mUnifierSource) {
        if (auto* unifier = SystemAccessor::getSoundSourceUnifier())
            unifier->freeSource(mUnifierSource, -1.0f);
        mUnifierSource = nullptr;
    }
}

/// Stops the sound immediately and finishes the source.
inline void SoundSource::finishNow_() {
    mPriority = 0.0f;
    mPlayingStateController->stopForce();
    if (mEmitter) {
        if (mEmitterNode.isLinked())
            mEmitter->removeSoundSource(this);
        mEmitter = nullptr;
    }
    mState = 7;
}

// 0x7100b777dc
void SoundSource::stopForce() {
    freeUnifierSource_();
    finishNow_();
}

// 0x7100b78478
void SoundSource::execOnFinalizeEmitter() {
    if (mPrepareFlags & 2) {
        if (!(mState >= 6 && mState < 8)) {
            if (mState <= 2) {
                finishNow_();
            } else {
                mStartDelayTime = 0.0f;
                mFadeInTime = 0.0f;
                beginToStop_();
            }
        }
    }
    mEmitter = nullptr;
}

// NON_MATCHING: same code; the original zeroes the return value after the state store (it reuses the null emitter register on the early path).
// 0x7100b770e4
bool SoundSource::setupSpatialCalcUnified_(bool* unified) {
    if (mSpatialCalculator) {
        *unified = false;
        return true;
    }

    if (mSpatialSetting.isPositioned()) {
        mSpatialCalculator = SystemAccessor::getArbiter()->getSpatialCalculatorPool()->alloc(
            mSpatialSetting.getCalculatorSetting(), mSpatialSetting.isCalculatorExclusive());
        if (!mSpatialCalculator)
            return false;
        if (!mUnifierSource)
            mUnifierSource = SystemAccessor::getSoundSourceUnifier()->allocSource(this);
        if (mUnifierSource) {
            *unified = true;
            return true;
        }
    }

    finishNow_();
    return false;
}

// 0x7100b77ca4
void SoundSource::stop(f32 fade_time, f32 release_time) {
    if (fade_time < 0.0f) {
        freeUnifierSource_();
        finishNow_();
        return;
    }

    if (mState >= 6 && mState < 8)
        return;

    if (mState <= 2) {
        finishNow_();
        return;
    }

    // The delay and fade-in time are not used any more once the sound plays: they hold the release parameters.
    mStartDelayTime = release_time;
    mFadeInTime = fade_time;
    if (release_time == 0.0f)
        beginToStop_();
    else
        mState = 5;
}

// 0x7100b772cc
void SoundSource::execOnDestroyWaveAsset(u64 a, u64 b, bool c, bool d) {
    if (mPlayingStateController->execOnDestroyWaveAsset(a, b, c, d))
        finishNow_();
}

// 0x7100b7900c
void SoundSource::execOnFianlizeSoundSourceUnifierSource() {
    if (mUnifierSource)
        finishNow_();
    mUnifierSource = nullptr;
}

// 0x7100b77f94
bool SoundSource::setReleaseTime(f32 release_time) {
    if (mState <= 2) {
        if (release_time < 0.0f && mSoundGroup)
            release_time = mSoundGroup->getReleaseTime();
        mPlayingStateController->setReleaseTime(sead::Mathf::clampMin(release_time, 0.0f));
        return true;
    }
    return false;
}

// 0x7100b778b8
void SoundSource::detachSoundGroup() {
    if (mSoundGroup) {
        mSoundGroup->removeSound(this);
        mSoundGroup = nullptr;
    }
}

// 0x7100b78134
bool SoundSource::prepare(bool prepare) {
    if (mState <= 2) {
        mPrepareFlags = !prepare ? mPrepareFlags & ~4 : mPrepareFlags | 4;
        return true;
    }
    return false;
}

// 0x7100b7816c
void SoundSource::setInteriorNum(s32 interior_num) {
    (void)mState;
    mInteriorNum = interior_num;
}

// 0x7100b77334
s32 SoundSource::getChannelNum(s32 track) const {
    if (track >= 0 && track < mTrackNum)
        return mChannelNum[track];
    return 0;
}

// 0x7100b780e8
bool SoundSource::setSpeakerBalanceSupplier(ISpeakerBalanceSupplier* supplier) {
    if (mState <= 2 && !mSpeakerBalanceSupplier) {
        mSpeakerBalanceSupplier = supplier;
        if (supplier)
            aggregateAndClampParams_();
        return true;
    }
    return false;
}

// 0x7100b7850c
bool SoundSource::isAttachedSound() const {
    return mPlayingStateController->mSoundController->mState != 0;
}

// 0x7100b78334
bool SoundSource::canVirtualize() const {
    return static_cast<s32>(mPlayingStateController->mVirtualizeMode) != 0 && !mSpatialSetting.isUnified();
}

// 0x7100b783d4
const SpatialCalculator::Result* SoundSource::getSpatialCalcResult(s32 index) const {
    if (!mSpatialSetting.isUnified() && mSpatialCalculator && mSpatialCalculator->getResultNum() > index)
        return mSpatialCalculator->getResult(index);
    return nullptr;
}

// 0x7100b782f4
const sead::SafeString& SoundSource::getSoundGroupName() const {
    return mSoundGroup ? mSoundGroup->getObjName() : sead::SafeString::cEmptyString;
}

// 0x7100b78428
f32 SoundSource::getAggregatedPriority() const {
    f32 priority = mPriority * mPriorityScale;
    if (mSpatialPlayingParam)
        priority *= mSpatialPlayingParam->mPriorityFactor;
    else if (mSpeakerBalanceSupplier)
        priority *= mSpeakerBalanceSupplier->getPriorityReduction();
    return priority;
}

// 0x7100b78a60
f32 SoundSource::getCurrentFadeInOutVolume() const {
    return SimpleTimedFader::toCurvedValue(mFadeCurveType, mFader->getValue());
}

// 0x7100b77850
void SoundSource::setTrackVolume(sead::BitFlag32 tracks, f32 volume) {
    if (volume >= 0.0f && volume <= 1.0f) {
        const u8 value = volume * 255.0f;
        for (s32 i = 0; i < 8; ++i) {
            if (tracks.isOnBit(i))
                mTrackVolume[i] = value;
        }
    }
}

inline void SoundSource::pauseImpl_(bool pause, f32 fade_time) {
    if (mSpatialSetting.isUnified()) {
        if (mUnifierSource)
            mUnifierSource->pause(pause, fade_time);
    } else {
        mPlayingStateController->pause(pause, fade_time);
    }
}

// 0x7100b77d78
void SoundSource::pause(sead::BitFlag8 mask, bool pause, f32 fade_time) {
    const u8 prev = mPauseFlags.getDirect();
    mPauseFlags.setDirect(pause ? prev | mask.getDirect() : prev & ~mask.getDirect());
    const u8 now = mPauseFlags.getDirect();
    if (prev == 0) {
        if (now != 0)
            pauseImpl_(true, fade_time);
    } else if (now == 0) {
        pauseImpl_(false, fade_time);
    }
}

}  // namespace aal
