#include "aal/aalSoundSourceUnifier.h"
#include <prim/seadScopedLock.h>
#include "aal/aalShape.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSpatialCalculator.h"

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
// 0x7100b8ee4c
void SoundSourceUnifierSource::initialize(SoundSource* sound_source) {
    mTarget = nullptr;
    mSoundSource = sound_source;
    mUnifiable = &mPosition;
    updatePosition_();
}

// 0x7100b8eed4
void SoundSourceUnifierSource::updatePosition_() {
    SpatialCalculator* calculator = mSoundSource->mSpatialCalculator;
    if (!calculator)
        return;

    if (Shape* shape = calculator->mSetting.shape) {
        mUnifiable = shape;
        return;
    }

    sead::ScopedLock<sead::CriticalSection> lock(&calculator->mCS);
    if (const sead::Matrix34f* matrix = calculator->mSetting.actor_matrix) {
        sead::Vector3f translation;
        matrix->getTranslation(translation);
        mPosition.mPosition = translation;
        mUnifiable = &mPosition;
    }
}

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
