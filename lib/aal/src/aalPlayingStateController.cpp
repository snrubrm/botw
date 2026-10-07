#include "aal/aalAssetInfo.h"
#include "aal/aalSettings.h"
#include "aal/aalSoundController.h"
#include "aal/aalSystemAccessor.h"

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
    mVirtualizeMode = VirtualizeMode(1);
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

// 0x7100b9fe58
bool PlayingStateController::restart_(u32 sample_pos, f32 fade_time) {
    if (!mSoundController)
        return false;

    mCS.lock();
    if (mState != 4) {
        mCS.unlock();
        return false;
    }

    mSoundController->setStartSampleOffset(sample_pos);
    const bool started = mSoundController->start(fade_time, false);
    if (started) {
        mState = 1;
        // The sound was paused while it was virtualized.
        if (mPaused && mSoundController) {
            mSoundController->pause(true, 0.0f);
            mPaused = true;
        }
    } else {
        mCS.lock();
        if (mSoundController)
            mSoundController->release(0.0f);
        mState = 0;
        mSamplePos = 0.0f;
        mPaused = false;
        mCS.unlock();
    }
    mCS.unlock();
    return started;
}

// 0x7100b9ffb0
void PlayingStateController::updateVirtualPlayingPos_() {
    if (mState != 3 || static_cast<s32>(mVirtualizeMode) != 4 || !mSoundController || mPaused)
        return;

    const AssetInfo* asset = mSoundController->mAssetInfo;
    if (!asset)
        return;

    AssetInfo::LoopInfo loop_info;
    if (!asset->getLoopInfo(&loop_info))
        return;

    mSamplePos += SystemAccessor::getSettings()->mCalcTimeStep * asset->getSampleRate();

    const f32 end = static_cast<f32>(static_cast<u32>(loop_info.loop_end));
    if (!(mSamplePos >= end))
        return;

    if (loop_info.is_looped) {
        const f32 length = static_cast<f32>(static_cast<u32>(loop_info.loop_end - loop_info.loop_start));
        do {
            mSamplePos -= length;
        } while (mSamplePos >= end);
        return;
    }

    // The virtual sound reached the end.
    mCS.lock();
    if (mSoundController)
        mSoundController->release(0.0f);
    mState = 0;
    mSamplePos = 0.0f;
    mPaused = false;
    mCS.unlock();
}

// NON_MATCHING: the original reads the state a second time after the first comparison (here it is one load) and, like
// stopWithRelease, stores the new state in separate branches (here a select).
// 0x7100ba00b8
bool PlayingStateController::virtualize() {
    mCS.lock();
    if (mState == 4) {
        mState = 3;
        mCS.unlock();
        return true;
    }
    const s32 state = mState;
    mCS.unlock();

    if (state != 1)
        return false;

    const s32 mode = static_cast<s32>(mVirtualizeMode);
    if (mode == 0)
        return false;

    if (mode == 1) {
        stopWithRelease();
        return true;
    }

    if (mSoundController) {
        if (mode == 2) {
            mSoundController->release(mReleaseTime);
            mSamplePos = 0.0f;
        } else {
            const s32 position = mSoundController->getPlayingSamplePos();
            if (position >= 0) {
                mSoundController->release(mReleaseTime);
                mSamplePos = static_cast<f32>(position);
            } else {
                mSamplePos = 0.0f;
            }
        }
    }

    mCS.lock();
    if (mState == 1)
        mState = 3;
    mCS.unlock();
    return true;
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

// NON_MATCHING: the same conditions, but the original keeps separate branches for the looped test and the two flags (this merges
// the flags with an and).
// 0x7100ba028c
bool PlayingStateController::execOnDestroyWaveAsset(u64 begin, u64 size, bool a, bool b) {
    const AssetInfo* asset = mSoundController->mAssetInfo;
    if (!asset || !(begin <= reinterpret_cast<u64>(asset->mAudioData) &&
                    begin + size > reinterpret_cast<u64>(asset->mAudioData)))
        return false;

    if (mState < 3 && (!(asset->mFlags & 1) || !b) && !a)
        return false;

    stopForce();
    return true;
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
