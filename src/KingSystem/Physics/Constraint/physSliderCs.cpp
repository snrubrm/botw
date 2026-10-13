#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"
#include "KingSystem/Physics/Constraint/physSliderCs.h"
#include "KingSystem/Physics/Constraint/physUnk_71024f6778.h"
#include "KingSystem/Physics/Constraint/physUnk_71024f67a8.h"
#include <Havok/Physics/Constraint/Data/Prismatic/hkpPrismaticConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

SliderCs::~SliderCs() = default;

void SliderCs::setMinMaxLimit(f32 min, f32 max) {
    mData->m_atoms.m_linLimit.m_min = min;
    mData->m_atoms.m_linLimit.m_max = max;
}

f32 SliderCs::sub_7100F71034() {
    return mData->m_atoms.m_linLimit.m_max;
}

f32 SliderCs::sub_7100F71040() {
    return mData->m_atoms.m_linLimit.m_min;
}

void SliderCs::sub_7100F71028(f32 friction) {
    mData->m_atoms.m_friction.m_maxFrictionForce = friction;
}

void SliderCs::sub_7100F7104C(bool allow_rotation) {
    mData->setAllowRotation(allow_rotation);
}

void SliderCs::sub_7100F71058(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b,
                            const sead::Vector3f& axis_a, const sead::Vector3f& axis_b,
                            const sead::Vector3f& perpendicular_a,
                            const sead::Vector3f& perpendicular_b) {
    hkVector4 hk_pivot_a;
    hkVector4 hk_pivot_b;
    hkVector4 hk_axis_a;
    hkVector4 hk_axis_b;
    hkVector4 hk_perpendicular_a;
    hkVector4 hk_perpendicular_b;
    loadFromVec3(&hk_pivot_a, pivot_a);
    loadFromVec3(&hk_pivot_b, pivot_b);
    loadFromVec3(&hk_axis_a, axis_a);
    loadFromVec3(&hk_axis_b, axis_b);
    loadFromVec3(&hk_perpendicular_a, perpendicular_a);
    loadFromVec3(&hk_perpendicular_b, perpendicular_b);
    mData->setInBodySpace(hk_pivot_a, hk_pivot_b, hk_axis_a, hk_axis_b,
                          hk_perpendicular_a, hk_perpendicular_b);
}
Unk_71024f6730::~Unk_71024f6730() = default;

// NON_MATCHING: limit/body loads and the Boolean OR operands use different scheduling/registers.
bool Unk_71024f6730::m0() const {
    const auto* instance = mConstraint->mConstraintInstance;
    const auto* data = static_cast<const hkpPrismaticConstraintData*>(instance->getData());
    const auto* body_a = instance->getRigidBodyA();
    const auto* body_b = instance->getRigidBodyB();
    const f32 min = data->m_atoms.m_linLimit.m_min + 0.1f;
    const f32 max = data->m_atoms.m_linLimit.m_max;
    const auto& transform_a = body_a ? body_a->getTransform() : hkTransform::getIdentity();
    const auto& transform_b = body_b ? body_b->getTransform() : hkTransform::getIdentity();
    hkVector4 pivot_a;
    hkVector4 pivot_b;
    hkVector4 axis;
    pivot_a.setTransformedPos(transform_a, data->m_atoms.m_transforms.m_transformA.getTranslation());
    pivot_b.setTransformedPos(transform_b, data->m_atoms.m_transforms.m_transformB.getTranslation());
    axis.setRotatedDir(transform_b.getRotation(),
                       data->m_atoms.m_transforms.m_transformB.getRotation().getColumn<0>());
    hkVector4 difference;
    difference.setSub(pivot_a, pivot_b);
    const f32 distance = difference.dot<3>(axis).val();
    return (distance <= min) | (distance >= max - 0.1f);
}

Unk_71024f6778::~Unk_71024f6778() = default;
Unk_71024f67a8::~Unk_71024f67a8() = default;

void Unk_71024f67a8::sub_7100F71CB4(Unk_71024f67a8* object) {
    delete object;
}

void Unk_71024f6778::sub_7100F719B4(Unk_71024f6778* object) {
    delete object;
}

void Unk_71024f6778::sub_7100F71A10() {
    _50 = 0.0f;
}

u32 sub_7100F70FB4(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x290 : 0x260);
}

}  // namespace ksys::phys
