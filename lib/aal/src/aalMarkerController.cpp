#include "aal/aalMarkerController.h"
#include "aal/aalSoundSource.h"

namespace aal {

// 0x7100b9f3f0
MarkerController::MarkerController()
    : mSoundSource(nullptr), _8(nullptr), mCallback(nullptr), mCallbackParam(0), mCallbackUserData(nullptr), _28(-1), _2c(0) {}

// 0x7100b9f408
void MarkerController::setup(SoundSource* sound_source) {
    mCallbackUserData = nullptr;
    mCallbackParam = 0;
    _8 = nullptr;
    mCallback = nullptr;
    mSoundSource = sound_source;
    _28 = -1;
    _2c = 0;
}

// 0x7100b9f424
void MarkerController::reset() {
    mSoundSource = nullptr;
    _8 = nullptr;
    mCallback = nullptr;
    mCallbackParam = 0;
    mCallbackUserData = nullptr;
    _28 = -1;
    _2c = 0;
}

// 0x7100b9f8ac
void MarkerController::setMarkerCallback(MarkerCallback callback, s32 param, void* user_data) {
    mCallback = callback;
    mCallbackParam = param;
    mCallbackUserData = user_data;
    if (mSoundSource)
        mSoundSource->mPrepareFlags |= 8;
}

}  // namespace aal
