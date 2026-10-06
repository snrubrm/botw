#include "aal/aalSoundSourceUnifier.h"

namespace aal {

// 0x7100b8ede4
SoundSourceUnifierSource::SoundSourceUnifierSource()
    : mSoundSource(nullptr), mUnifiable(nullptr), mTarget(nullptr) {}

// NON_MATCHING: the original also stores the vtable pointer of the IUnifiable base (the position member) at the end.
// 0x7100b8ee10
SoundSourceUnifierSource::~SoundSourceUnifierSource() {
    finalize();
}

// 0x7100b8ee2c
void SoundSourceUnifierSource::finalize() {
    mTarget = nullptr;
    mSoundSource = nullptr;
    mUnifiable = nullptr;
}

// NON_MATCHING: the original copies the 16 bytes of the handle in forward order (ldp/stp), the member copy here goes
// backwards (SROA splits the copy).
// 0x7100b8ef58
Handle SoundSourceUnifierSource::getTargetHandle() const {
    if (mTarget)
        return mTarget->mHandle;
    return Handle();
}

// NON_MATCHING: same copy order difference as getTargetHandle.
// 0x7100b8ef88
void SoundSourceUnifierSource::pause(bool pause, f32 fade_time) {
    if (mTarget) {
        Handle handle = mTarget->mHandle;
        handle.pause(pause, fade_time);
    }
}

}  // namespace aal
