#include "KingSystem/Physics/Constraint/physRackAndPinionCs.h"
#include <Havok/Physics/Constraint/Data/RackAndPinion/hkpRackAndPinionConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/Constraint/physUnk_71024f6640.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::phys {

RackAndPinionCs* RackAndPinionCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpRackAndPinionConstraintData), 16))
        hkpRackAndPinionConstraintData;
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8) RackAndPinionCs(instance, body_a, body_b, breakable, data);
    constraint->sub_7100F6A180(heap);
    const f32 pitch = param.pinion_radius_or_screw_pitch;
    const bool is_screw = param.is_screw;
    hkVector4 pivot_a;
    hkVector4 pivot_b;
    hkVector4 axis_a;
    hkVector4 axis_b;
    loadFromVec3(&pivot_a, param.pivot_a);
    loadFromVec3(&pivot_b, param.pivot_b);
    loadFromVec3(&axis_a, param.axis_a);
    loadFromVec3(&axis_b, param.axis_b);
    constraint->mData->sub_71015F815C(pivot_a, pivot_b, axis_a, axis_b, is_screw, pitch);
    return constraint;
}

RackAndPinionCs::~RackAndPinionCs() = default;
Unk_71024f6640::~Unk_71024f6640() = default;

u32 sub_7100F703FC(bool breakable, bool) {
    return sub_7100F6ACF4(breakable) + 0x1a0;
}

// The common callback lifetime follows the derived constraint families.
Unk_71012a6844::ItemA::ItemA(Constraint* constraint) : mConstraint(constraint) {}
Unk_71012a6844::ItemA::~ItemA() = default;

void Unk_71012a6844::ItemA::sub_7100F6EC20(sead::Vector3f*, sead::Vector3f*) const {}
void Unk_71012a6844::ItemA::sub_7100F6FF60(sead::Vector3f*, sead::Vector3f*) const {}

void Unk_71012a6844::ItemA::sub_7100F70C48(ItemA* item) {
    System::instance()->sub_7101216AB0(item);
    delete item;
}

}  // namespace ksys::phys

Unk_71024f6670::~Unk_71024f6670() = default;
