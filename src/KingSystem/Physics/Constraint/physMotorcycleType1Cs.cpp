#include "KingSystem/Physics/Constraint/physMotorcycleType1Cs.h"
#include <Havok/Physics/Constraint/Data/Generic/hkpGenericConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

MotorcycleType1Cs::~MotorcycleType1Cs() = default;

// NON_MATCHING: the inline generic-data constructor schedules the vptr and the
// atom type stores in a different order.
MotorcycleType1Cs* MotorcycleType1Cs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpGenericConstraintData), 16)) hkpGenericConstraintData;
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8) MotorcycleType1Cs(instance, body_a, body_b, breakable, data);
    constraint->sub_7100F6A180(heap);
    return constraint;
}

void MotorcycleType1Cs::sub_7100F6F1B4(f32 value) {
    mData->m_atoms.m_linFriction.m_maxFrictionForce = value;
}

}  // namespace ksys::phys
