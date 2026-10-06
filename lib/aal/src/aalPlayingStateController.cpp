#include "aal/aalSoundController.h"

namespace aal {

// 0x7100b9fd14
void PlayingStateController::setReleaseTime(f32 release_time) {
    if (release_time >= 0.0f)
        mReleaseTime = release_time;
}

// 0x7100ba025c
s32 PlayingStateController::getPlayingSamplePos() const {
    if (mState != 0) {
        if (mState == 3)
            return static_cast<s32>(mSamplePos);
        if (mSoundController)
            return mSoundController->getPlayingSamplePos();
    }
    return -1;
}

// 0x7100b9fd24
void PlayingStateController::setVirtualizeMode(VirtualizeMode mode) {
    mVirtualizeMode = mode;
}

// 0x7100b9fb60
PlayingStateController::PlayingStateController() = default;

// 0x7100b9fb8c / 0x7100b9fc20
PlayingStateController::~PlayingStateController() {
    finalize();
}

// 0x7100b9fbe0
void PlayingStateController::finalize() {
    if (mSoundController) {
        mSoundController->finalize();
        delete mSoundController;
        mSoundController = nullptr;
    }
}

// 0x7100b9fc7c
void PlayingStateController::initialize(sead::Heap* heap) {
    mSoundController = new (heap, 8) SoundController;
    if (mSoundController)
        mSoundController->initialize(heap);
}

// 0x7100b9fcd8
void PlayingStateController::reset() {
    if (mSoundController)
        mSoundController->reset();
    mState = 0;
    mVirtualizeMode = static_cast<VirtualizeMode>(1);
    mPaused = false;
    mReleaseTime = 0.0f;
    _20 = 0.0f;
    mSamplePos = 0.0f;
}

// 0x7100b9fd2c
bool PlayingStateController::start(bool prepare) {
    if (mSoundController) {
        mSoundController->release(0.0f);
        if (mSoundController->start(0.0f, prepare)) {
            mState = 1;
            return true;
        }
    }
    return false;
}

// 0x7100b9fd8c: NON_MATCHING (the original stores the two state values in separate branches; here they are merged into a select)
void PlayingStateController::stopWithRelease() {
    const f32 release_time = mReleaseTime;
    mCS.lock();
    if (!mSoundController) {
        mState = 0;
    } else {
        mSoundController->release(release_time);
        if (release_time == 0.0f)
            mState = 0;
        else
            mState = 2;
    }
    mSamplePos = 0.0f;
    mPaused = false;
    mCS.unlock();
}

// 0x7100b9fdf4
void PlayingStateController::stopForce() {
    mCS.lock();
    if (mSoundController)
        mSoundController->release(0.0f);
    mState = 0;
    mSamplePos = 0.0f;
    mPaused = false;
    mCS.unlock();
}

// 0x7100b9fe3c
void PlayingStateController::preCalc() {
    if (mState == 4)
        restart_(static_cast<u32>(mSamplePos), _20);
}

// 0x7100b9ff50: NON_MATCHING (the original reads mState again for the second comparison)
void PlayingStateController::calc() {
    if (mSoundController) {
        mSoundController->calc();
        if (mState >= 1 && mState <= 2 && mSoundController->mState == 0) {
            mState = 0;
            updateVirtualPlayingPos_();
        }
    }
}

// 0x7100ba01d8
void PlayingStateController::unvirtualize() {
    mCS.lock();
    if (mState == 3) {
        if (static_cast<s32>(mVirtualizeMode) == 2)
            mSamplePos = 0.0f;
        mState = 4;
    }
    mCS.unlock();
}

// 0x7100ba0228
void PlayingStateController::pause(bool pause, f32 fade_time) {
    if (mSoundController) {
        mSoundController->pause(pause, fade_time);
        mPaused = pause;
    }
}

}  // namespace aal
