#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadThread.h>

namespace aal {

/// A cone around the z axis of an actor matrix: `calcRate` returns how far a position is inside the
/// cone (0 within the start angle, 1 beyond the end angle, linear in between). Cones are allocated from the
/// pool of the ConeFactory.
class Cone {
public:
    Cone();
    virtual ~Cone() = default;

    void setActorMatrix(const sead::Matrix34f& matrix);
    void getPosition(sead::Vector3f* out) const;
    /// Sets the angles in radians: `end` is clamped to [0, pi], `start` to [0, end].
    void setAngle(f32 start, f32 end);
    /// The angle between the cone axis and the direction from the cone position to `position`.
    f32 calcAngle(const sead::Vector3f& position) const;
    f32 calcRate(const sead::Vector3f& position) const;
    /// Same as calcRate, but `position` is relative to the cone position.
    f32 calcRateOriginShiftPos(const sead::Vector3f& position) const;

private:
    sead::Matrix34f mMatrix;
    sead::Vector3f mDirection;
    f32 mAngleStart;
    f32 mAngleEnd;
    f32 mAngleRange;
};
static_assert(sizeof(Cone) == 0x50, "aal::Cone size mismatch");

/// The pool of the cones (sead::ObjList of Cone: the list node follows each cone in the pool, so a pool entry is 0x60 bytes).
class ConeFactory : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ConeFactory)
public:
    ConeFactory() = default;
    virtual ~ConeFactory();

    void initialize(s32 num, sead::Heap* heap);
    /// nullptr if the pool is full or was not initialized.
    Cone* create();
    void destroy(Cone* cone);

private:
    sead::ObjList<Cone> mCones;
    sead::CriticalSection mCS;
};

}  // namespace aal
