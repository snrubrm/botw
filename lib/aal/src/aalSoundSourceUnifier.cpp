#include "aal/aalSoundSourceUnifier.h"
#include <prim/seadScopedLock.h>
#include "aal/aalArbiter.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b8e420
SoundSourceUnifier::SoundSourceUnifier() : mInitialized(false), _b0(false), _b4(560.0f), _b8(450.0f) {}

// 0x7100b8e490
SoundSourceUnifier::~SoundSourceUnifier() {
    finalize();
}

// 0x7100b8eb1c
void SoundSourceUnifier::initialize(const InitializeArg& arg, sead::Heap* heap) {
    if (mInitialized)
        return;

    mSources.tryAllocBuffer(arg.source_num, heap, 8);
    mTargets.tryAllocBuffer(arg.target_num, heap, 8);
    mInitialized = true;
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

// NON_MATCHING: same code except for the search of the target: the original loop keeps a status word (0 / 4: keep
// searching, 1: found, 2: end of the list) and selects the found target with a csel instead of leaving the loop, and it
// keeps the list node of the new source / target in a register for the failure path.
// 0x7100b8e604
SoundSourceUnifierSource* SoundSourceUnifier::allocSource(SoundSource* sound_source) {
    if (!mInitialized)
        return nullptr;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    SoundSourceUnifierSource* source = mSources.emplaceBack();
    if (!source)
        return nullptr;

    source->initialize(sound_source);

    SoundSourceUnifierCondition condition;
    if (sound_source->getAssetName())
        condition.name.copy(sound_source->getAssetName());
    condition.sound_group = sound_source->mSoundGroup;
    condition._58.first = sound_source->isLooped() ? 0 : SystemAccessor::getArbiter()->get_8();

    SoundSourceUnifierTarget* target = nullptr;
    for (SoundSourceUnifierTarget& t : mTargets) {
        if (t.mName.isEqual(condition.name) && t._70.first == condition._58.first &&
            t.mSoundGroup == condition.sound_group) {
            if (t.mSources.size() != 0) {
                target = &t;
                break;
            }
        }
    }

    if (!target) {
        target = mTargets.emplaceBack();
        if (!target)
            return nullptr;

        target->initialize(condition);

        SoundSource::SetupInfo setup;
        setup.sound_group = sound_source->mSoundGroup;
        setup._8 = nullptr;
        setup.prepare_flags = sound_source->mPrepareFlags;
        // volatile: the original stores the result to the stack, reloads it for the comparison and reads it once more
        // (an unused load) on the failure path.
        volatile StartResult result = target->startSound(*sound_source->getAssetInfo(), &setup);
        if (result > StartResult::Success) {
            (void)result;
            target->finalize();
            mTargets.erase(target);
            source->finalize();
            mSources.erase(source);
            return nullptr;
        }
        target->setParamsFromSoundSourceFirst(sound_source);
    }

    target->addSource(source);
    source->mTarget = target;
    return source;
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
