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

}  // namespace aal
