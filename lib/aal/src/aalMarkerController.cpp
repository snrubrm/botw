#include "aal/aalMarkerController.h"

namespace aal {

// 0x7100b9f3f0
MarkerController::MarkerController()
    : mSoundSource(nullptr), _8(nullptr), _10(nullptr), _18(0), _20(0), _28(-1), _2c(0) {}

// 0x7100b9f408
void MarkerController::setup(SoundSource* sound_source) {
    _20 = 0;
    _18 = 0;
    _8 = nullptr;
    _10 = nullptr;
    mSoundSource = sound_source;
    _28 = -1;
    _2c = 0;
}

// 0x7100b9f424
void MarkerController::reset() {
    mSoundSource = nullptr;
    _8 = nullptr;
    _10 = nullptr;
    _18 = 0;
    _20 = 0;
    _28 = -1;
    _2c = 0;
}

}  // namespace aal
