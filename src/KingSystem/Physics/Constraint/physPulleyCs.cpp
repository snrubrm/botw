#include <Havok/Physics/Constraint/Data/Pulley/hkpPulleyConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/Constraint/physPulleyCs.h"
#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"

namespace ksys::phys {

// Adjacent constraint lifetime families at 0x7100f6ee80 and 0x7100f6f7c8.
PulleyCs::~PulleyCs() = default;

void PulleyCs::sub_7100F6F7F0(f32 length) {
    mData->m_atoms.m_pulley.m_ropeLength = length;
}

void PulleyCs::sub_7100F6F7FC(f32 leverage) {
    mData->m_atoms.m_pulley.m_leverageOnBodyB = leverage;
}

f32 PulleyCs::sub_7100F6F808() const {
    return mData->m_atoms.m_pulley.m_leverageOnBodyB;
}
Unk_71024f65c8::~Unk_71024f65c8() = default;

// Whether either side of the rope is (nearly) taut.
bool Unk_71024f65c8::m0() const {
    const auto* instance = mConstraint->mConstraintInstance;
    const auto* body_a = instance->getRigidBodyA();
    const auto* body_b = instance->getRigidBodyB();
    const auto& transform_a = body_a ? body_a->getTransform() : hkTransform::getIdentity();
    const auto& transform_b = body_b ? body_b->getTransform() : hkTransform::getIdentity();
    const auto* data = static_cast<const hkpPulleyConstraintData*>(instance->getData());
    const auto& pulley = data->m_atoms.m_pulley;

    hkVector4 pivot_a;
    pivot_a.setTransformedPos(transform_a, data->m_atoms.m_translations.m_translationA);
    hkVector4 rope_a;
    rope_a.setSub(pivot_a, pulley.m_fixedPivotAinWorld);
    if (rope_a.length<3>() > pulley.m_ropeLength - 0.1f)
        return true;

    hkVector4 pivot_b;
    pivot_b.setTransformedPos(transform_b, data->m_atoms.m_translations.m_translationB);
    hkVector4 rope_b;
    rope_b.setSub(pivot_b, pulley.m_fixedPivotBinWorld);
    return rope_b.length<3>() > pulley.m_ropeLength * pulley.m_leverageOnBodyB - 0.1f;
}

u32 sub_7100F6F790(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x1a0 : 0x170);
}

}  // namespace ksys::phys
