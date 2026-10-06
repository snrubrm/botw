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

/// Limits the number of sounds of a group. TODO: partial; the object has a vtable at +0.
class GroupLimiter {
public:
    void initialize(Group* group, sead::Heap* heap);
    void finalize();
    void calc();
    bool limitRequestInterval(SoundSource* source);
    /// 0x7100b80170 / 0x7100b80274 (declared only)
    void calcActiveSoundLimit();
    void calcRequestSoundLimit();
    /// 0x7100b8029c / 0x7100b802d8 / 0x7100b80314 (declared only)
    void updateUpperActiveSoundLimitList();
    void updateUpperRequestSoundLimitList();
    void updateUsingRequestIntervalLimiter();
    /// 0x7100b80354 (declared only)
    void addToActiveSoundLimitList(sead::OffsetList<SoundSource>* sources);
    /// 0x7100b8040c (declared only): returns whether the sound was added to the limit list.
    bool addToActiveSoundLimitList(SoundSource* source);

private:
    u8 _0[8];
    bool mInitialized;
    Group* mGroup;
    u8 _18[0x28 - 0x18];
    RequestIntervalLimiter* mRequestIntervalLimiter;
    u8 _30[0x50 - 0x30];
    RequestIntervalLimiter* mRequestIntervalLimiterForLimit;
};

/// Ducks the volume of a group while other groups play. TODO: only calc is declared (0x7100b82ba0).
class GroupDucker {
public:
    void calc();
};

}  // namespace aal
