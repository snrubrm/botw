#include "aal/aalRequestSoundLimiter.h"
#include "aal/aalGroup.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSoundSourceSortFuncs.h"

namespace aal {

// 0x7100b83720
RequestSoundLimiter::RequestSoundLimiter() = default;

// 0x7100b8374c
void RequestSoundLimiter::setup(const Settings& settings) {
    mSettings = settings;
    if (mSettings.mField1 < 0)
        mSettings.mField1 = 0;
    if (!(mSettings.mField2 >= 0.0f))
        mSettings.mField2 = 0.0f;
    if (!(mSettings.mField3 <= 1.0f && mSettings.mField3 >= 0.0f))
        mSettings.mField3 = 1.0f;
    if (!(mSettings.mField4 <= 1.0f && mSettings.mField4 >= 0.0f))
        mSettings.mField4 = 1.0f;
}

// NON_MATCHING: native branch layout, robust-list traversal and register allocation differ.
void RequestSoundLimiter::calcLimit(sead::OffsetList<SoundSource>* sound_sources,
                                    sead::OffsetList<SoundSource>* upper_sound_sources) {
    if (mSettings.mLimitNum < 0) {
        for (SoundSource& source : sound_sources->robustRange()) {
            if (source.mState <= 1)
                continue;
            sound_sources->erase(&source);
            if (upper_sound_sources)
                upper_sound_sources->pushBack(&source);
            else if (source.mSoundGroup)
                source.mSoundGroup->addToPlayingSoundSources(&source);
        }
        return;
    }
    if (mSettings.mLimitNum == 0) {
        for (SoundSource& source : sound_sources->robustRange()) {
            sound_sources->erase(&source);
            source.stopForce();
        }
        return;
    }
    if (mSettings.mFlag)
        sound_sources->insertionSort(SoundSourceSortFuncs::comparePriorityIgnoreStopOrVirtual);
    else
        sound_sources->insertionSort(SoundSourceSortFuncs::comparePriority);
    s32 accepted = 0;
    for (SoundSource& source : sound_sources->robustRange()) {
        if (source.mState <= 1)
            continue;
        sound_sources->erase(&source);
        if (upper_sound_sources)
            upper_sound_sources->pushBack(&source);
        else if (source.mSoundGroup)
            source.mSoundGroup->addToPlayingSoundSources(&source);
        if (++accepted >= mSettings.mLimitNum)
            break;
    }
    s32 delay_num = mSettings.mField1;
    f32 delay = mSettings.mField2;
    f32 scale = mSettings.mField3;
    f32 priority_scale = mSettings.mField4;
    for (SoundSource& source : sound_sources->robustRange()) {
        const s32 state = source.mState;
        if (state <= 1)
            continue;
        if (delay_num > 0 && state == 2) {
            if (source.setStartDelayTime(delay)) {
                source._d8 = scale * source._d8;
                source.mPriorityScale = priority_scale * source.mPriorityScale;
                scale *= mSettings.mField3;
                delay += mSettings.mField2;
                priority_scale *= mSettings.mField4;
                --delay_num;
            }
        } else {
            sound_sources->erase(&source);
            source.stopForce();
        }
    }
}

}  // namespace aal
