#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The speaker layout of the room a listener is in (the subclasses are the speaker setups).
/// TODO: incomplete (the object has a vtable at +0).
class Interior {
public:
    /// Ignores sizes that are not positive.
    void setInteriorSize(f32 size);
    f32 getInteriorSizeAsInGameLength() const;
    f32 getFrontSpeakerAngle() const;
    f32 getRearSpeakerAngle() const;
    /// Ignores gains outside of [0, 1].
    void setRearSpeakerGain(f32 gain);

private:
    u8 _0[0x20];
    f32 mInteriorSize;
    u8 _24[4];
    f32 mRearSpeakerGain;
    /// The angles are in sead angle indices (see Mathf::idx2rad).
    u32 mFrontSpeakerAngle;
    u32 mRearSpeakerAngle;
};

}  // namespace aal
