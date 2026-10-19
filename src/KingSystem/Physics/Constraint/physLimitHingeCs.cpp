#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"
#include <Havok/Physics/Constraint/Data/LimitedHinge/hkpLimitedHingeConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

LimitHingeCs::~LimitHingeCs() = default;

// NON_MATCHING: the Constraint value temporary occupies a different 4-byte stack slot.
LimitHingeCs* LimitHingeCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpLimitedHingeConstraintData), 16))
        hkpLimitedHingeConstraintData;
    data->m_atoms.m_angLimit.m_maxAngle = param.max_angle;
    data->m_atoms.m_angLimit.m_minAngle = param.min_angle;
    data->m_atoms.m_angFriction.m_maxFrictionTorque = param.max_friction_torque;
    data->m_atoms.m_angLimit.m_angularLimitsTauFactor = param.angular_limits_tau_factor;
    hkVector4 pivot_a;
    hkVector4 pivot_b;
    hkVector4 axis_a;
    hkVector4 axis_b;
    hkVector4 axis_a2;
    hkVector4 axis_b2;
    loadFromVec3(&pivot_a, param.pivot_a);
    loadFromVec3(&pivot_b, param.pivot_b);
    loadFromVec3(&axis_a, param.axis_a);
    loadFromVec3(&axis_b, param.axis_b);
    loadFromVec3(&axis_a2, param.axis_a2);
    loadFromVec3(&axis_b2, param.axis_b2);
    data->sub_71015F1E18(pivot_a, pivot_b, axis_a, axis_b, axis_a2, axis_b2);
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8) LimitHingeCs(instance, body_a, body_b, breakable, data);
    if (param._20) {
        auto* item = new (heap, 8) Unk_71024f6420(constraint);
        constraint->_20 = item;
    }
    constraint->sub_7100F6A180(heap);
    return constraint;
}

void LimitHingeCs::sub_7100F6E300(f32 angle) {
    mData->m_atoms.m_angLimit.m_minAngle = angle;
    mData->m_atoms.m_angLimit.m_maxAngle = angle;
}

void LimitHingeCs::sub_7100F6E314(f32 min_angle, f32 max_angle) {
    mData->m_atoms.m_angLimit.m_minAngle = min_angle;
    mData->m_atoms.m_angLimit.m_maxAngle = max_angle;
}

void LimitHingeCs::sub_7100F6E328(f32 torque) {
    mData->m_atoms.m_angFriction.m_maxFrictionTorque = torque;
}

void LimitHingeCs::sub_7100F6E334(f32 tau_factor) {
    mData->m_atoms.m_angLimit.m_angularLimitsTauFactor = tau_factor;
}

f32 LimitHingeCs::sub_7100F6E340() const {
    return mData->m_atoms.m_angLimit.m_maxAngle;
}

f32 LimitHingeCs::sub_7100F6E34C() const {
    return mData->m_atoms.m_angLimit.m_minAngle;
}

f32 LimitHingeCs::sub_7100F6E358() const {
    return mData->m_atoms.m_angLimit.m_angularLimitsTauFactor;
}

Unk_71024f6420::~Unk_71024f6420() = default;

u32 sub_7100F6E2A0(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x240 : 0x210);
}

}  // namespace ksys::phys
