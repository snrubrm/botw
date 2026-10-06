#include "aal/aalShape.h"
#include <gfx/seadPrimitiveRenderer.h>
#include <prim/seadScopedLock.h>
#include "aal/aalShapeMgr.h"
#include "aal/aalSpatialCalculator.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// NON_MATCHING: the original stores the NamedObj vtable after the name member is set up, and the member stores are not merged
// 0x7100b9a26c
Shape::Shape(const sead::SafeString& name) : NamedObj(name) {
    mSpatialCalculators.initOffset(offsetof(SpatialCalculator, mShapeListNode));
}

// NON_MATCHING: register allocation of the list walk (the original keeps the offset-adjusted end pointer in one register)
// 0x7100b9a46c
void Shape::destroy() {
    {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        for (SpatialCalculator& calculator : mSpatialCalculators)
            calculator.detachShape(true);
        mSpatialCalculators.clear();
    }
    SystemAccessor::getShapeMgr()->removeShape(this);
    delete this;
}

// NON_MATCHING (D1 0x7100b9a334 and its thunk): the original base destructor keeps the final store of the IUnifiable vtable
// pointer (this + 0x18); D0 0x7100b9a3dc matches
// 0x7100b9a334 / 0x7100b9a3dc
Shape::~Shape() = default;

// 0x7100b9a520
void Shape::setPosition(const sead::Vector3f& position) {
    if (!mFlags.isOnBit(KeepPosition))
        mMatrix.setTranslation(position);
}

// 0x7100b9a544
void Shape::setRotate(const sead::Matrix34f& rotation) {
    if (!mFlags.isOnBit(KeepRotation)) {
        sead::Vector3f translation;
        mMatrix.getTranslation(translation);
        mMatrix = rotation;
        mMatrix.setTranslation(translation);
    }
}

// NON_MATCHING: same arithmetic, but the original builds the rows in a different vector register order
// 0x7100b9a580
void Shape::setRotate(const sead::Vector3f& rotation) {
    if (!mFlags.isOnBit(KeepRotation)) {
        sead::Matrix34f matrix;
        matrix.makeR(rotation);
        sead::Vector3f translation;
        mMatrix.getTranslation(translation);
        mMatrix = matrix;
        mMatrix.setTranslation(translation);
    }
}

// 0x7100b9a8f0
void Shape::getPositionWithOffset(sead::Vector3f* out) const {
    out->setMul(mMatrix, mOffset);
}

// 0x7100b9a6a0
void Shape::setActorMatrix(const sead::Matrix34f& matrix) {
    if (mFlags.isOnBit(KeepPosition)) {
        if (!mFlags.isOnBit(KeepRotation)) {
            sead::Vector3f translation;
            mMatrix.getTranslation(translation);
            mMatrix = matrix;
            mMatrix.setTranslation(translation);
        }
    } else if (mFlags.isOnBit(KeepRotation)) {
        sead::Vector3f translation;
        matrix.getTranslation(translation);
        mMatrix.setTranslation(translation);
    } else {
        mMatrix = matrix;
    }
}

// 0x7100b9aa60
void Shape::setActorMatrixFromSpatialCalculator_(const sead::Matrix34f& matrix) {
    if (mFlags.isOnBit(KeepPosition)) {
        if (!mFlags.isOnBit(KeepRotation)) {
            sead::Vector3f translation;
            matrix.getTranslation(translation);
            mMatrix.setTranslation(translation);
        } else {
            mMatrix = matrix;
        }
    } else if (mFlags.isOnBit(KeepRotation)) {
        sead::Vector3f translation;
        mMatrix.getTranslation(translation);
        mMatrix = matrix;
        mMatrix.setTranslation(translation);
    }
}

// 0x7100b9a968
void Shape::attachSpatialCalculator_(SpatialCalculator* calculator) {
    if (!calculator || mSpatialCalculators.isNodeLinked(calculator))
        return;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mSpatialCalculators.pushBack(calculator);
}

// 0x7100b9a9e8
void Shape::detachSpatialCalculator_(SpatialCalculator* calculator) {
    if (!calculator)
        return;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (mSpatialCalculators.indexOf(calculator) >= 0)
        mSpatialCalculators.erase(calculator);
}

// 0x7100b9aba0
void Shape::setShapeParam(const sead::Vector3f& vector, const sead::Vector3f& rotation,
                          bool position_at_bottom) {}

// 0x7100b9aba4
void Shape::setRadius(f32 radius) {}

// 0x7100b9aba8
f32 Shape::getRadius() const {
    return 0.0f;
}

// 0x7100b9abb0
void Shape::setVector(const sead::Vector3f& vector) {}

// 0x7100b9abb4
const sead::Vector3f& Shape::getVector() const {
    return sead::Vector3f::zero;
}

// 0x7100b9abc0
void Shape::setUp(const sead::Vector3f& up) {}

// 0x7100b9abc4
const sead::Vector3f& Shape::getUp() const {
    return sead::Vector3f::ey;
}

// 0x7100b9abd0
void Shape::drawShape_(sead::PrimitiveDrawer& drawer, const sead::Color4f& color, f32 scale) const {}

}  // namespace aal
