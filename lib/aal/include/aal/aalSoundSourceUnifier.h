#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalHandle.h"
#include "aal/aalSoundSource.h"
#include "aal/aalStartResult.h"
#include "aal/aalUnifiablePosition.h"

namespace sead {
class Heap;
}

namespace aal {

class AssetInfo;
class SoundGroup;
class SoundSourceUnifierTarget;
class SpeakerBalanceUnifier;

/// What the sounds have to have in common to be unified (SoundSourceUnifier::allocSource builds it on the stack from the
/// sound source and compares it with the condition of every target).
struct SoundSourceUnifierCondition {
    /// Purpose unknown (copied as a whole by the target). Only `first` is ever initialized (the constructors of the
    /// condition and of the target store just the first word).
    struct Pair {
        s32 first = 0;
        s32 second;
    };

    /// The name of the asset; the speaker balance unifier of the target is named after it.
    SoundSourceUnifierCondition() {
        name.clear();
        _58.first = 0;
        sound_group = nullptr;
    }

    sead::FixedSafeString<64> name;
    Pair _58;
    SoundGroup* sound_group;
};
static_assert(sizeof(SoundSourceUnifierCondition) == 0x68, "aal::SoundSourceUnifierCondition size mismatch");

/// The part of a unified (merged) group of sounds that belongs to one SoundSource: the position of the sound source
/// (its own or, when it follows a shape, the shape's) that is unified in the target.
/// TODO: incomplete (initialize and updatePosition_ are declared only).
class SoundSourceUnifierSource {
public:
    SoundSourceUnifierSource();
    ~SoundSourceUnifierSource();

    void initialize(SoundSource* sound_source);
    void finalize();
    void updatePosition_();
    void pause(bool pause, f32 fade_time);
    /// The handle of the sound that plays the unified sources.
    Handle getTargetHandle() const;

private:
    friend class SoundSourceUnifier;
    friend class SoundSourceUnifierTarget;

    SoundSource* mSoundSource;
    /// Either the own position (mPosition) or the unifiable of the shape of the sound source.
    IUnifiable* mUnifiable;
    UnifiablePosition mPosition;
    SoundSourceUnifierTarget* mTarget;
    sead::ListNode mTargetListNode;
};
static_assert(sizeof(SoundSourceUnifierSource) == 0x60, "aal::SoundSourceUnifierSource size mismatch");

/// A sound that is played for all the SoundSourceUnifierSource that were added to it.
/// TODO: incomplete (initialize, calc, setParamsFromSoundSource, startSound are declared only).
class SoundSourceUnifierTarget {
public:
    SoundSourceUnifierTarget();
    ~SoundSourceUnifierTarget();

    void initialize(const SoundSourceUnifierCondition& condition);
    void finalize();
    void calc();
    /// Copies the sound parameters of the sound source to the target sound.
    void setParamsFromSoundSource(SoundSource* sound_source);
    /// Sets up the unifier and the sound with the settings of the first sound source (then calls setParamsFromSoundSource).
    void setParamsFromSoundSourceFirst(SoundSource* sound_source);
    StartResult startSound(const AssetInfo& asset, SoundSource::SetupInfo* setup);
    void stopSound(f32 fade_time);
    void addSource(SoundSourceUnifierSource* source);
    void removeSource(SoundSourceUnifierSource* source);
    bool isActive() const;

private:
    friend class SoundSourceUnifier;
    friend class SoundSourceUnifierSource;

    SpeakerBalanceUnifier* mUnifier;
    Handle mHandle;
    sead::FixedSafeString<64> mName;
    SoundSourceUnifierCondition::Pair _70;
    SoundGroup* mSoundGroup;
    sead::OffsetList<SoundSourceUnifierSource> mSources;
};
static_assert(sizeof(SoundSourceUnifierTarget) == 0x98, "aal::SoundSourceUnifierTarget size mismatch");

/// TODO: incomplete (initialize, allocSource, freeSource and calc are declared only).
class SoundSourceUnifier : public sead::hostio::Node {
public:
    struct InitializeArg {
        /// The maximum number of sound sources and of unified sounds.
        s32 source_num;
        s32 target_num;
    };

    SoundSourceUnifier();
    ~SoundSourceUnifier();

    void initialize(const InitializeArg& arg, sead::Heap* heap);
    void finalize();
    /// Returns nullptr if there is no room left for the source or its target.
    SoundSourceUnifierSource* allocSource(SoundSource* sound_source);
    /// A negative fade time stops the target immediately.
    void freeSource(SoundSourceUnifierSource* source, f32 fade_time);
    void calc();

private:
    bool mInitialized;
    sead::ObjList<SoundSourceUnifierSource> mSources;
    sead::ObjList<SoundSourceUnifierTarget> mTargets;
    sead::CriticalSection mCS;
    bool _b0;
    f32 _b4;
    f32 _b8;
};

}  // namespace aal
