#pragma once

#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalIUnifiable.h"
#include "aal/aalNamedObj.h"

namespace sead {
class Color4f;
class Heap;
class PrimitiveDrawer;
}  // namespace sead

namespace aal {

class Listener;
class SpatialCalculator;

/// A 3D shape that a sound is positioned against (the closest point on the shape to the listener is
/// the sound position). Created through the `create` function of a concrete shape, which allocates
/// the shape on a heap and registers it with the ShapeMgr; `destroy` unregisters and deletes it.
class Shape : public NamedObj, public IUnifiable, public sead::hostio::Node {
    SEAD_RTTI_BASE(Shape)
public:
    /// Bits of `mFlags`: when a bit is set, the matching part of the shape's transform is kept when
    /// the position / rotation / actor matrix is set.
    enum Flag {
        KeepPosition = 0,
        KeepRotation = 1,
        /// calcUnifiablePositions: the position that the angle is calculated with is searched separately.
        SeparateAnglePosition = 2,
    };

    explicit Shape(const sead::SafeString& name);
    ~Shape() override;

    /// Detaches the shape from all spatial calculators, removes it from the ShapeMgr and deletes it.
    void destroy();

    /// `position_at_bottom`: the shape position is the bottom (base) of the shape instead of its center.
    virtual void setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                               bool position_at_bottom);
    virtual void calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const = 0;
    virtual void setRadius(f32 radius);
    virtual f32 getRadius() const;
    virtual void setVector(const sead::Vector3f& vector);
    virtual const sead::Vector3f& getVector() const;
    virtual void setUp(const sead::Vector3f& up);
    virtual const sead::Vector3f& getUp() const;
    bool calcUnifiablePositions(const Listener& listener, sead::Vector3f* a,
                                sead::Vector3f* b) override;

    void setPosition(const sead::Vector3f& position);
    void setRotate(const sead::Matrix34f& rotation);
    void setRotate(const sead::Vector3f& rotation);
    void setActorMatrix(const sead::Matrix34f& matrix);

    bool calcPositionByListener(const Listener& listener, sead::Vector3f* out) const;
    bool calcPositionForAngle(const Listener& listener, sead::Vector3f* out) const;
    void getPositionWithOffset(sead::Vector3f* out) const;

protected:
    virtual void drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color,
                            f32 scale) const;

    void attachSpatialCalculator_(SpatialCalculator* calculator);
    void detachSpatialCalculator_(SpatialCalculator* calculator);
    void setActorMatrixFromSpatialCalculator_(const sead::Matrix34f& matrix);

    void* _48 = nullptr;
    void* _50 = nullptr;
    sead::Matrix34f mMatrix = sead::Matrix34f::ident;
    sead::Vector3f mOffset = sead::Vector3f::zero;

public:
    sead::BitFlag8 mFlags;

protected:
    sead::OffsetList<SpatialCalculator> mSpatialCalculators;
    sead::CriticalSection mCS;
};


/// A line segment (`getVector` is its direction and length).
class ShapeSegment : public Shape {
    SEAD_RTTI_OVERRIDE(ShapeSegment, Shape)
public:
    explicit ShapeSegment(const sead::SafeString& name) : Shape(name) {}

    static ShapeSegment* create(const sead::SafeString& name, sead::Heap* heap);

    void setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                       bool position_at_bottom) override;
    void calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const override;
    void setVector(const sead::Vector3f& vector) override { mVector = vector; }
    const sead::Vector3f& getVector() const override { return mVector; }

protected:
    void drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color,
                    f32 scale) const override;

    sead::Vector3f mVector = sead::Vector3f::ey;
};
static_assert(sizeof(ShapeSegment) == 0x100, "aal::ShapeSegment size mismatch");

/// A box (`getVector` is its size along each axis, all components non-negative; negative vectors are ignored).
class ShapeCube : public Shape {
    SEAD_RTTI_OVERRIDE(ShapeCube, Shape)
public:
    explicit ShapeCube(const sead::SafeString& name) : Shape(name) {}

    static ShapeCube* create(const sead::SafeString& name, sead::Heap* heap);

    /// Same as setVector (0x7100b9b49c; the virtual one is 0x7100b9bb4c).
    void setSize(const sead::Vector3f& size);

    void setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                       bool position_at_bottom) override;
    void calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const override;
    void setVector(const sead::Vector3f& vector) override;
    const sead::Vector3f& getVector() const override { return mVector; }

protected:
    void drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color,
                    f32 scale) const override;

    sead::Vector3f mVector;
};
static_assert(sizeof(ShapeCube) == 0x100, "aal::ShapeCube size mismatch");

/// A cylinder around the axis `getVector` (axis direction and length) with a radius.
class ShapeCylinder : public Shape {
    SEAD_RTTI_OVERRIDE(ShapeCylinder, Shape)
public:
    explicit ShapeCylinder(const sead::SafeString& name) : Shape(name) {}

    static ShapeCylinder* create(const sead::SafeString& name, sead::Heap* heap);

    void setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                       bool position_at_bottom) override;
    void calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const override;
    void setRadius(f32 radius) override {
        if (radius >= 0.0f)
            mRadius = radius;
    }
    f32 getRadius() const override { return mRadius; }
    void setVector(const sead::Vector3f& vector) override { mVector = vector; }
    const sead::Vector3f& getVector() const override { return mVector; }

protected:
    void drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color,
                    f32 scale) const override;

    sead::Vector3f mVector = sead::Vector3f::ey;
    f32 mRadius = 1.0f;
};
static_assert(sizeof(ShapeCylinder) == 0x100, "aal::ShapeCylinder size mismatch");

/// A capsule: a cylinder with hemispherical ends around the segment `getVector` (axis direction and length). It has
/// the same members as ShapeCylinder.
class ShapeCapsule : public Shape {
    SEAD_RTTI_OVERRIDE(ShapeCapsule, Shape)
public:
    explicit ShapeCapsule(const sead::SafeString& name) : Shape(name) {}

    static ShapeCapsule* create(const sead::SafeString& name, sead::Heap* heap);

    void setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                       bool position_at_bottom) override;
    void calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const override;
    void setRadius(f32 radius) override {
        if (radius >= 0.0f)
            mRadius = radius;
    }
    f32 getRadius() const override { return mRadius; }
    void setVector(const sead::Vector3f& vector) override { mVector = vector; }
    const sead::Vector3f& getVector() const override { return mVector; }

protected:
    void drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color,
                    f32 scale) const override;

    sead::Vector3f mVector = sead::Vector3f::ey;
    f32 mRadius = 1.0f;
};
static_assert(sizeof(ShapeCapsule) == 0x100, "aal::ShapeCapsule size mismatch");

/// A sphere with a radius.
class ShapeSphere : public Shape {
    SEAD_RTTI_OVERRIDE(ShapeSphere, Shape)
public:
    explicit ShapeSphere(const sead::SafeString& name) : Shape(name) {}

    static ShapeSphere* create(const sead::SafeString& name, sead::Heap* heap);

    void setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                       bool position_at_bottom) override;
    void calcPosition(const sead::Vector3f& source, sead::Vector3f* out) const override;
    void setRadius(f32 radius) override {
        if (radius >= 0.0f)
            mRadius = radius;
    }
    f32 getRadius() const override { return mRadius; }

protected:
    void drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color,
                    f32 scale) const override;

    f32 mRadius = 1.0f;
};
static_assert(sizeof(ShapeSphere) == 0xf8, "aal::ShapeSphere size mismatch");

}  // namespace aal
