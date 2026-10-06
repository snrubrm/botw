#include "aal/aalSoundSourceUnifier.h"

namespace aal {

// 0x7100b8e420
SoundSourceUnifier::SoundSourceUnifier() : mInitialized(false), _b0(false), _b4(560.0f), _b8(450.0f) {}

// 0x7100b8e490
SoundSourceUnifier::~SoundSourceUnifier() {
    finalize();
}

// 0x7100b8e4c4
void SoundSourceUnifier::finalize() {
    if (mInitialized) {
        auto end = mTargets.end();
        for (auto it = mTargets.begin(); it != end;) {
            SoundSourceUnifierTarget& target = *it;
            ++it;
            target.finalize();
        }
        mSources.freeBuffer();
        mTargets.freeBuffer();
        mInitialized = false;
    }
}

}  // namespace aal
