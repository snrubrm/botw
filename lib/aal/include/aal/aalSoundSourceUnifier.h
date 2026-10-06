#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalHandle.h"
#include "aal/aalUnifiablePosition.h"

namespace sead {
class Heap;
}

namespace aal {

class SoundSource;
class SoundSourceUnifierTarget;
class SpeakerBalanceUnifier;

/// What the sounds have to have in common to be unified.
/// TODO: incomplete (only the members that SoundSourceUnifierTarget::initialize reads are modeled).
struct SoundSourceUnifierCondition {
    /// Purpose unknown (copied as a whole by the target).
    struct Pair {
        s32 first;
        s32 second;
    };

    /// The name of the speaker balance unifier.
    sead::SafeString name;
    u8 _10[0x58 - 0x10];
    Pair _58;
    void* _60;
};

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
    /// 0x7100b8f2a4 (declared only): copies the sound parameters of the sound source to the target sound.
    void setParamsFromSoundSource(SoundSource* sound_source);
    void stopSound(f32 fade_time);
    void addSource(SoundSourceUnifierSource* source);
    void removeSource(SoundSourceUnifierSource* source);
    bool isActive() const;

private:
    friend class SoundSourceUnifierSource;

    SpeakerBalanceUnifier* mUnifier;
    Handle mHandle;
    sead::FixedSafeString<64> mName;
    SoundSourceUnifierCondition::Pair _70;
    void* _78;
    sead::OffsetList<SoundSourceUnifierSource> mSources;
};
static_assert(sizeof(SoundSourceUnifierTarget) == 0x98, "aal::SoundSourceUnifierTarget size mismatch");

/// TODO: incomplete (initialize, allocSource, freeSource and calc are declared only).
class SoundSourceUnifier : public sead::hostio::Node {
public:
    struct InitializeArg;

    SoundSourceUnifier();
    ~SoundSourceUnifier();

    /// 0x7100b8eb1c (declared only)
    void initialize(const InitializeArg& arg, sead::Heap* heap);
    void finalize();
    /// 0x7100b8e604 (declared only)
    SoundSourceUnifierSource* allocSource(SoundSource* sound_source);
    /// 0x7100b8ea64 (declared only): a negative fade time stops the target immediately.
    void freeSource(SoundSourceUnifierSource* source, f32 fade_time);
    /// 0x7100b8eca4 (declared only)
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
