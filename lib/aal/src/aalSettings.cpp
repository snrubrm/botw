#include "aal/aalSettings.h"
#include <audio/seadAudioMgr.h>
#include "aal/aalOutputDevice.h"
#include "aal/aalSDKFoundation.h"
#include "aal/aalSystem.h"
#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100ba0df8
Settings::~Settings() {
    if (mOutputDevices[0]) {
        delete mOutputDevices[0];
        mOutputDevices[0] = nullptr;
    }
}

namespace {

// The output modes of aal and of the sound library are not in the same order.
inline sead::AudioGlobal::OutputMode toAudioOutputMode(OutputMode mode) {
    static const sead::AudioGlobal::OutputMode cOutputModes[3] = {
        sead::AudioGlobal::OutputMode(1), sead::AudioGlobal::OutputMode(0), sead::AudioGlobal::OutputMode(2)};
    const s32 index = mode;
    return static_cast<u32>(index) <= 2 ? cOutputModes[index] : sead::AudioGlobal::OutputMode(4);
}

}  // namespace

// NON_MATCHING: the original stores the third speaker balance mode before the first two (which are one 64-bit store).
// 0x7100ba0d28
Settings::Settings() {
    mOutputDevices[0] = nullptr;
    mMasterVolume = 1.0f;
    mBaseFPS = 60.0f;
    mFrameWaitIntervalStepRate = 1.0f;
    mCalcTimeStep = 1.0f / 60.0f;
    mLengthPerMeter = 1.0f;
    mLengthPerMeterSquared = 1.0f;
    mSoundSpeed = 340.0f;
    mSoundDistancePerFrame = 340.0f / 60.0f;
    mDopplerPitchMin = 0.25f;
    mDopplerPitchMax = 4.0f;
    mDopplerMode = 0;
    mTVOutputVolume = 1.0f;
    mBuildInSpeakerOutputVolume = 2.0f;
    mStereoJackOutputVolume = 2.0f;
    _50 = 0xffff;
    mSpeakerBalanceModes[0] = SpeakerBalanceMode(0);
    mSpeakerBalanceModes[1] = SpeakerBalanceMode(0);
    mSpeakerBalanceModes[2] = SpeakerBalanceMode(0);
    mOutputModes[0] = OutputMode(2);

    if (sead::AudioMgr* audio_mgr = System::sInstance->mAudioMgr)
        audio_mgr->getAudioSystem()->setOutputMode(toAudioOutputMode(mOutputModes[0]));
    else
        System::sInstance->mSDKFoundation->setOutputMode(mOutputModes[0], DeviceType(0));
}

// 0x7100ba0f90
void Settings::setOutputMode(OutputMode mode, DeviceType device) {
    mOutputModes[device] = mode;
    mOutputDevices[device]->changeInterior(mode);

    if (sead::AudioMgr* audio_mgr = System::sInstance->mAudioMgr)
        audio_mgr->getAudioSystem()->setOutputMode(toAudioOutputMode(mOutputModes[0]));
    else
        System::sInstance->mSDKFoundation->setOutputMode(mOutputModes[0], DeviceType(0));

    if (SpeakerBalanceUnifierMgr* mgr = SystemAccessor::getSpeakerBalanceUnifierMgr()) {
        mgr->setupUnifierSpeakerBalanceTable();
        mgr->setupInteriorSize();
    }
}

// 0x7100ba0f80
void Settings::calc() {
    mOutputDevices[0]->calc();
}

// 0x7100ba10f4
void Settings::setSpeakerBalanceMode(OutputMode output_mode, SpeakerBalanceMode mode) {
    mSpeakerBalanceModes[output_mode] = mode;
    if (SpeakerBalanceUnifierMgr* mgr = SystemAccessor::getSpeakerBalanceUnifierMgr()) {
        mgr->setupUnifierSpeakerBalanceTable();
        mgr->setupInteriorSize();
    }
}

// 0x7100ba1148
SpeakerBalanceMode Settings::getCurrentSpeakerBalanceMode(DeviceType device) const {
    return getSpeakerBalanceMode(mOutputModes[device]);
}

// 0x7100ba104c
void Settings::setBaseFPS(f32 fps) {
    if (fps > 0.0f) {
        mSoundDistancePerFrame = mSoundSpeed * mLengthPerMeter / fps;
        mBaseFPS = fps;
        mCalcTimeStep = mFrameWaitIntervalStepRate / fps;
    }
}

// 0x7100ba107c
void Settings::setFrameWaitIntervalStepRate(f32 rate) {
    if (rate > 0.0f) {
        mFrameWaitIntervalStepRate = rate;
        mCalcTimeStep = rate / mBaseFPS;
    }
}

// 0x7100ba1094
void Settings::setLengthPerMeter(f32 length) {
    if (length > 0.0f) {
        mLengthPerMeter = length;
        mLengthPerMeterSquared = length * length;
        mSoundDistancePerFrame = mSoundSpeed * length / mBaseFPS;
    }
}

// 0x7100ba10bc
f32 Settings::getDopplerPitchMin() const {
    return mDopplerMode == 1 ? 1.0f : mDopplerPitchMin;
}

// 0x7100ba10d8
f32 Settings::getDopplerPitchMax() const {
    return mDopplerMode == 1 ? 1.0f : mDopplerPitchMax;
}

}  // namespace aal
