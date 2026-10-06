#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace aal {

class Shape;

/// How a sound source is positioned in space. The matrix and velocity are stored here, and the
/// 0x38-byte block at 0x48 is the aal::SpatialCalculator::Setting that is handed to the spatial
/// calculator: it points back at the matrix and the velocity.
class SpatialSetting {
public:
    SpatialSetting();
    virtual ~SpatialSetting();

    /// Makes the sound follow the shape (the sound position is the point of the shape closest to
    /// the listener).
    void setShape(Shape* shape);

    void setPositioned(bool positioned);
    void setPositionFollow(bool follow);
    /// Also points the spatial calculator setting at the stored matrix / velocity.
    void setActorMatrix(const sead::Matrix34f& matrix);
    void setVelocity(const sead::Vector3f& velocity);
    void getPosition(sead::Vector3f* position) const;
    void setDopplerFactor(f32 factor);
    /// Ignores negative sizes; the size is converted with aal::Meter::toLength.
    void setSoundSourceSize(f32 size);
    void setUnified(bool unified);
    void setUseSoundSourceSizeForAttenuation(bool enable);
    void setRotatingStereoEnabled(bool enable);
    void setListenerDirectivityEnabled(bool enable);
    void setUserParam(u64 param);
    bool isUnified() const { return mFlags & 2; }

private:
    sead::Matrix34f mActorMatrix;
    sead::Vector3f mVelocity;
    bool mPositioned;
    bool mPositionFollow;
    u8 _46;
    // aal::SpatialCalculator::Setting (0x48..0x80):
    const sead::Matrix34f* _48;
    const sead::Vector3f* _50;
    void* _58;
    f32 mDopplerFactor;
    f32 mSoundSourceSize;
    Shape* mShape;
    u16 mFlags;
    u16 _72;
    u64 mUserParam;
};
static_assert(sizeof(SpatialSetting) == 0x80, "aal::SpatialSetting size mismatch");

}  // namespace aal
