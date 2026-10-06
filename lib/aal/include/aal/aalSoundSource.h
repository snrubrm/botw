#pragma once

#include <basis/seadTypes.h>
#include <cstddef>

#include "aal/aalSpatialCalculator.h"
#include "aal/aalSpatialSetting.h"

namespace aal {

/// A playing sound (the object a Handle refers to).
/// TODO: incomplete. Only the members that are read through a Handle are declared; the rest of the
/// object (sound parameters, fade state, player pointers...) is not decompiled yet. The constructor
/// ends with a zeroed 0x50-byte block at 0x1a0, right after the spatial setting.
class SoundSource {
public:
    virtual ~SoundSource();

    /// Life cycle state: 0 is unused and 7 is finished; states up to 2 are the ones before playback
    /// starts (the start delay is counted down in state 1).
    u8 _8;
    s32 mState;
    u32 mId;
    u8 _14[0x120 - 0x14];
    SpatialSetting mSpatialSetting;
    /// Allocated from the spatial calculator pool when the sound is positioned in space; nullptr if none.
    SpatialCalculator* mSpatialCalculator;
};
static_assert(offsetof(SoundSource, mState) == 0xc, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mId) == 0x10, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mSpatialSetting) == 0x120, "aal::SoundSource layout mismatch");
static_assert(offsetof(SoundSource, mSpatialCalculator) == 0x1a0, "aal::SoundSource layout mismatch");

}  // namespace aal
