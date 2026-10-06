#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

namespace aal {

/// Calculates the spatial parameters (distance attenuation, angle, doppler...) of a sound source for each
/// listener, from a SpatialCalculator::Setting.
/// TODO: incomplete. Only the functions that game code calls and the reference count / result count are declared.
class SpatialCalculator {
public:
    /// The spatial calculation result for one listener (0x98 bytes, not modeled).
    struct Result {
        u8 _0[0x98];
    };

    /// Detaches the calculator from its shape; with `reset_position`, also forgets the position/matrix
    /// pointers of the setting. Returns whether a shape was attached.
    bool detachShape(bool reset_position);

    /// The calculator is shared by the sounds that use it (0x7100b8fe28 / 0x7100b8fe38 / 0x7100b8fe4c).
    void beginReferred();
    void endReferred();
    bool isReferred() const;
    /// 0x7100b8fb00: the number of results of the last calculation (0 if there are none).
    s32 getResultNum() const;
    /// 0x7100b8fab8: nullptr if the index is out of range.
    const Result* getResult(s32 index) const;

private:
    u8 _0[0x64];
    s32 mReferredCount;
    u8 _68[0x80 - 0x68];
    /// volatile: the original reads the count again for the bounds check of the result.
    volatile s32 mResultNum;
    u8 _84[4];
    Result* mResults;
};

/// The spatial parameters of a sound that are shared with the playing state. TODO: only the priority factor is
/// declared.
class SpatialPlayingParam {
public:
    u8 _0[0x18];
    /// Multiplied into the priority of the sound source.
    f32 mPriorityFactor;
};

}  // namespace aal
