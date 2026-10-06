#include "aal/aalSoundSourceUnifier.h"
#include "aal/aalEmitter.h"
#include "aal/aalGroup.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSpatialCalculator.h"
#include "aal/aalSpeakerBalanceUnifier.h"
#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// NON_MATCHING: the two stores of the trailing members come after the list initialization in the original.
// 0x7100b8efc8
SoundSourceUnifierTarget::SoundSourceUnifierTarget() : mUnifier(nullptr), _70{}, _78(nullptr) {
    mSources.initOffset(offsetof(SoundSourceUnifierSource, mTargetListNode));
}

// 0x7100b8f060
SoundSourceUnifierTarget::~SoundSourceUnifierTarget() {
    finalize();
}

// 0x7100b8f0b8
void SoundSourceUnifierTarget::finalize() {
    if (mUnifier) {
        SystemAccessor::getSpeakerBalanceUnifierMgr()->freeSpeakerBalanceUnifier(mUnifier);
        mUnifier = nullptr;
    }
    mSources.clear();
    mName.clear();
    _70.first = 0;
    _78 = nullptr;
}

// 0x7100b8f110
void SoundSourceUnifierTarget::initialize(const SoundSourceUnifierCondition& condition) {
    mName.copy(condition.name);
    _78 = condition._60;
    const sead::SafeString& name = mName;
    _70 = condition._58;
    mUnifier = SystemAccessor::getSpeakerBalanceUnifierMgr()->allocSpeakerBalanceUnifier(name, nullptr);
}

// 0x7100b8f224
void SoundSourceUnifierTarget::calc() {
    s32 index = 0;
    for (SoundSourceUnifierSource& source : mSources) {
        if (index++ == 0)
            setParamsFromSoundSource(source.mSoundSource);
        source.updatePosition_();
    }
}

// 0x7100b8f2a4
void SoundSourceUnifierTarget::setParamsFromSoundSource(SoundSource* sound_source) {
    if (SoundSource* target = mHandle.getSoundSource()) {
        SoundParam::copy(&target->mDefaultParam, sound_source->mDefaultParam);
        SoundParam::copy(&target->mParam, sound_source->mParam);
        target->setPriority(sound_source->mPriority);
    }

    if (mUnifier) {
        f32 spread = sound_source->mDefaultParam.getSpread() + sound_source->mParam.getSpread();
        if (sound_source->mEmitter)
            spread += sound_source->mEmitter->getSpread();
        if (sound_source->mSoundGroup)
            spread += sound_source->mSoundGroup->getAggregatedParam()->getSpread();
        mUnifier->setSpread(spread);
    }
}

// 0x7100b8f454
void SoundSourceUnifierTarget::setParamsFromSoundSourceFirst(SoundSource* sound_source) {
    if (mUnifier) {
        if (SpatialCalculator* calculator = sound_source->mSpatialCalculator) {
            mUnifier->setAttenuator(calculator->mSetting.attenuator);
            mUnifier->mInteriorMask = calculator->mSetting._2a;
            const s32 interior_num = sound_source->mInteriorNum;
            mUnifier->setInteriorNum(interior_num);
            mUnifier->setListenerDirectivityEnabled((calculator->mSetting.flags >> 5) & 1);
        }
    }

    const f32 fade_in_time = sound_source->getFadeInTimeIfBeforePlaying();
    if (fade_in_time >= 0.0f)
        mHandle.setFadeInTime(fade_in_time);
    mHandle.setFadeCurveType(sound_source->mFadeCurveType);
    setParamsFromSoundSource(sound_source);
}

// NON_MATCHING: same code, but the original keeps the result in the lower half of an 8-byte stack slot (sp+8), here it is at
// sp+12 (StartResult is probably wider or aligned differently in the original).
// 0x7100b8f348
StartResult SoundSourceUnifierTarget::startSound(const AssetInfo& asset, SoundSource::SetupInfo* setup) {
    if (!mUnifier)
        return StartResult::NoUnifier;

    StartResult result = StartResult::Success;
    mHandle = mUnifier->emit(asset, setup, &result);
    return result;
}

// 0x7100b8f38c
void SoundSourceUnifierTarget::stopSound(f32 fade_time) {
    mHandle.stop(fade_time, 0.0f);
}

// 0x7100b8f398
void SoundSourceUnifierTarget::addSource(SoundSourceUnifierSource* source) {
    if (source && mUnifier && source->mUnifiable) {
        mUnifier->addUnifiable(source->mUnifiable);
        mSources.pushBack(source);
    }
}

// 0x7100b8f3ec
void SoundSourceUnifierTarget::removeSource(SoundSourceUnifierSource* source) {
    if (source && mUnifier) {
        if (source->mUnifiable)
            mUnifier->removeUnifiable(source->mUnifiable);
        if (mSources.isNodeLinked(source))
            mSources.erase(source);
    }
}

// 0x7100b8f44c
bool SoundSourceUnifierTarget::isActive() const {
    return mHandle.isActive();
}

}  // namespace aal
