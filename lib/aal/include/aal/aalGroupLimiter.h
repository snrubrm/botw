#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include "aal/aalTimedFader.h"

namespace sead {
class Heap;
}

namespace aal {

class Group;
class SoundSource;
class RequestIntervalLimiter;

class ActiveSoundLimiter;
class RequestSoundLimiter;

/// Limits the number of sounds of a group. The limiters can be set per group; a group without a limiter of its own
/// uses the one of the nearest ancestor that has one (the `Upper` / `Using` pointers).
/// TODO: partial; the object has a vtable at +0.
class GroupLimiter {
public:
    GroupLimiter();
    virtual ~GroupLimiter();

    void initialize(Group* group, sead::Heap* heap);
    void finalize();
    void calc();
    bool limitRequestInterval(SoundSource* source);
    /// 0x7100b80170 / 0x7100b80274 (declared only)
    void calcActiveSoundLimit();
    void calcRequestSoundLimit();
    void updateUpperActiveSoundLimitList();
    void updateUpperRequestSoundLimitList();
    void updateUsingRequestIntervalLimiter();
    /// 0x7100b80354 (declared only)
    void addToActiveSoundLimitList(sead::OffsetList<SoundSource>* sources);
    /// 0x7100b8040c (declared only): returns whether the sound was added to the limit list.
    bool addToActiveSoundLimitList(SoundSource* source);
    void setActiveSoundLimiter(ActiveSoundLimiter* limiter, sead::OffsetList<SoundSource>* sources);
    void setRequestSoundLimiter(RequestSoundLimiter* limiter, sead::OffsetList<SoundSource>* sources);
    void setRequestIntervalLimiter(RequestIntervalLimiter* limiter);

private:
    bool mInitialized;
    Group* mGroup;
    ActiveSoundLimiter* mActiveSoundLimiter;
    RequestSoundLimiter* mRequestSoundLimiter;
    RequestIntervalLimiter* mRequestIntervalLimiter;
    /// The sounds of the group that are counted by the limiters (set together with the limiter).
    sead::OffsetList<SoundSource>* mActiveSoundLimitList;
    sead::OffsetList<SoundSource>* mRequestSoundLimitList;
    /// The lists of the nearest ancestor that has a limiter (the request interval limiter that is used is the one of
    /// the OUTERMOST group that has one).
    sead::OffsetList<SoundSource>* mUpperActiveSoundLimitList;
    sead::OffsetList<SoundSource>* mUpperRequestSoundLimitList;
    RequestIntervalLimiter* mRequestIntervalLimiterForLimit;
    u8 _58[6];
    s32 _60;
    u16 _64;
    s32 _68;
    s32 _6c;
    s32 _70;
    f32 _74;
    f32 _78;
    u8 _7c;
    s32 _80;
};
static_assert(sizeof(GroupLimiter) == 0x88, "aal::GroupLimiter size mismatch");

class IDuckingSource;

/// Ducks the volume of a group while other groups play. TODO: incomplete (the targets are not modeled).
class GroupDucker : public sead::hostio::Node {
public:
    struct Settings {
        f32 _0;
        f32 _4;
        f32 _8;
    };
    struct TargetSettings {
        f32 _0;
        f32 _4;
        f32 _8;
    };

    /// A group whose sounds duck the group of the ducker.
    class Target {
    public:
        /// Whether the volume of the fader is changing.
        bool isFaderMoving() const;
        f32 getFaderVolume() const;

    private:
        Group* mGroup;
        TargetSettings mSettings;
        TimedFader mFader;
        sead::ListNode mListNode;
    };
    static_assert(sizeof(Target) == 0x50, "aal::GroupDucker::Target size mismatch");

    explicit GroupDucker(IDuckingSource* source);
    virtual ~GroupDucker();

    void initialize(sead::Heap* heap);
    void finalize();
    void setup(const Settings& settings);
    void calc();
    /// Stops the ducking (the state is not the idle one).
    void suspend();
    void resetState();

private:
    bool mInitialized;
    Settings mSettings;
    s32 mState;
    u8 _1c[4];
    IDuckingSource* mSource;
    sead::OffsetList<Target> mTargets;
    s32 _40;
    s32 _44;
};
static_assert(sizeof(GroupDucker) == 0x48, "aal::GroupDucker size mismatch");

}  // namespace aal
