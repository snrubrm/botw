#include "aal/aalSoundSourceUnifier.h"
#include <prim/seadScopedLock.h>
#include "aal/aalSoundSource.h"

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

// 0x7100b8ea64
void SoundSourceUnifier::freeSource(SoundSourceUnifierSource* source, f32 fade_time) {
    if (!mInitialized)
        return;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (SoundSourceUnifierTarget* target = source->mTarget) {
        target->removeSource(source);
        if (target->mSources.size() == 0)
            target->stopSound(fade_time);
    }
    source->finalize();
    mSources.erase(source);
}

// NON_MATCHING: the original walks the targets by their list node (it keeps the node of the current target for the
// erase), here the node is recomputed from the object.
// 0x7100b8eca4
void SoundSourceUnifier::calc() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    auto end = mTargets.end();
    for (auto it = mTargets.begin(); it != end;) {
        SoundSourceUnifierTarget& target = *it;
        ++it;
        if (target.isActive()) {
            target.calc();
            continue;
        }

        auto sources_end = target.mSources.end();
        for (auto source_it = target.mSources.begin(); source_it != sources_end;) {
            SoundSourceUnifierSource& source = *source_it;
            ++source_it;
            if (source.mSoundSource)
                source.mSoundSource->execOnFianlizeSoundSourceUnifierSource();
            target.removeSource(&source);
            source.finalize();
            mSources.erase(&source);
        }
        target.finalize();
        mTargets.erase(&target);
    }
}

}  // namespace aal
