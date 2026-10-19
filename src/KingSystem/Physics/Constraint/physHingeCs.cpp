#include "KingSystem/Physics/Constraint/physHingeCs.h"
#include <Havok/Physics/Constraint/Data/Hinge/hkpHingeConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

HingeCs::~HingeCs() = default;

// NON_MATCHING: vector loads and the constructor argument's stack slot differ.
HingeCs* HingeCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpHingeConstraintData), 16)) hkpHingeConstraintData;
    hkVector4 pivot_a;
    hkVector4 pivot_b;
    hkVector4 axis_a;
    hkVector4 axis_b;
    loadFromVec3(&pivot_a, param.pivot_a);
    loadFromVec3(&pivot_b, param.pivot_b);
    loadFromVec3(&axis_a, param.axis_a);
    loadFromVec3(&axis_b, param.axis_b);
    data->sub_71015F6B54(pivot_a, pivot_b, axis_a, axis_b);
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

// NON_MATCHING: the compiler loads the vector components separately.
void HingeCs::sub_7100F6DEAC(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b,
                            const sead::Vector3f& axis_a, const sead::Vector3f& axis_b) {
    mData->sub_71015F6B54(toHkVec4(pivot_a), toHkVec4(pivot_b), toHkVec4(axis_a), toHkVec4(axis_b));
}

sead::Vector3f HingeCs::sub_7100F6DF30() const {
    sead::Vector3f axis;
    storeToVec3(&axis, mData->m_atoms.m_transforms.m_transformA.getRotation().getColumn(0));
    return axis;
}

u32 sub_7100F6DC48(bool breakable, bool) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

}  // namespace ksys::phys

namespace ksys::phys {

// 0x7100f6dbb0 (unnamed): builds the default hinge parameters and calls HingeCs::make.
HingeCs* sub_7100F6DBB0(sead::Heap* heap) {
    HingeCs::Param param;
    return HingeCs::make(param, heap);
}

}  // namespace ksys::phys
