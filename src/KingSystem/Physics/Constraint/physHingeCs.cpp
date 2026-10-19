#include "KingSystem/Physics/Constraint/physHingeCs.h"
#include <Havok/Physics/Constraint/Data/Hinge/hkpHingeConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

HingeCs::~HingeCs() = default;

HingeCs* HingeCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpHingeConstraintData), 16)) hkpHingeConstraintData;
    data->sub_71015F6B54(toHkVec4(param.pivot_a), toHkVec4(param.pivot_b),
                        toHkVec4(param.axis_a), toHkVec4(param.axis_b));
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8) HingeCs(instance, body_a, body_b, breakable, data);
    constraint->sub_7100F6A180(heap);
    return constraint;
}

void HingeCs::sub_7100F6DEAC(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b,
                            const sead::Vector3f& axis_a, const sead::Vector3f& axis_b) {
    hkVector4 pivot_a_hk;
    hkVector4 pivot_b_hk;
    hkVector4 axis_a_hk;
    hkVector4 axis_b_hk;
    loadFromVec3(&pivot_a_hk, pivot_a);
    loadFromVec3(&pivot_b_hk, pivot_b);
    loadFromVec3(&axis_a_hk, axis_a);
    loadFromVec3(&axis_b_hk, axis_b);
    mData->sub_71015F6B54(pivot_a_hk, pivot_b_hk, axis_a_hk, axis_b_hk);
}

sead::Vector3f HingeCs::sub_7100F6DF30() const {
    sead::Vector3f axis;
    storeToVec3(&axis, mData->m_atoms.m_transforms.m_transformA.getRotation().getColumn(0));
    return axis;
}

u32 sub_7100F6DC48(bool breakable, bool) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

// 0x7100f6dbb0 (unnamed): builds the default hinge parameters and calls HingeCs::make.
HingeCs* sub_7100F6DBB0(sead::Heap* heap) {
    HingeCs::Param param;
    return HingeCs::make(param, heap);
}

}  // namespace ksys::phys
