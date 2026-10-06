#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Calculates the spatial parameters (distance attenuation, angle, doppler...) of a sound source for each
/// listener, from a SpatialCalculator::Setting.
/// TODO: incomplete. Only the functions that game code calls and the reference count / result count are declared.
class SpatialCalculator {
public:
    /// Detaches the calculator from its shape; with `reset_position`, also forgets the position/matrix
    /// pointers of the setting. Returns whether a shape was attached.
    bool detachShape(bool reset_position);

    /// The calculator is shared by the sounds that use it (0x7100b8fe28 / 0x7100b8fe38 / 0x7100b8fe4c).
    void beginReferred();
    void endReferred();
    bool isReferred() const;
    /// 0x7100b8fb00: the number of results of the last calculation (0 if there are none).
    s32 getResultNum() const;

private:
    u8 _0[0x64];
    s32 mReferredCount;
    u8 _68[0x80 - 0x68];
    s32 mResultNum;
    u8 _84[4];
    void* mResults;
};

}  // namespace aal
