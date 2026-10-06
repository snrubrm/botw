#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>

namespace sead {
class Heap;
}

namespace aal {

class Group;
class SoundSource;

/// Limits how often a sound can be requested in a group. TODO: only the members GroupLimiter calls are declared
/// (0x7100b83650 / 0x7100b836c4).
class RequestIntervalLimiter {
public:
    void calc();
    bool limit(SoundSource* source);
};

class ActiveSoundLimiter;
class RequestSoundLimiter;

/// Limits the number of sounds of a group. The limiters can be set per group; a group without a limiter of its own
/// uses the one of the nearest ancestor that has one (the `Upper` / `Using` pointers).
/// TODO: partial; the object has a vtable at +0.
class GroupLimiter {
public:
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
};

/// Ducks the volume of a group while other groups play. TODO: only calc is declared (0x7100b82ba0).
class GroupDucker {
public:
    void calc();
};

}  // namespace aal
