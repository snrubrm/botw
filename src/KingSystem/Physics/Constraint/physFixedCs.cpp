#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include <Havok/Physics/Constraint/Data/Fixed/hkpFixedConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <heap/seadHeap.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

u32 sub_7100F6D3DC(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

FixedCs::~FixedCs() = default;

FixedCs* FixedCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpFixedConstraintData), 16)) hkpFixedConstraintData;
    hkTransform frame_a;
    hkTransform frame_b;
    toHkTransform(&frame_a, param.mtx_a);
    toHkTransform(&frame_b, param.mtx_b);
    data->sub_71015F3F90(frame_a, frame_b);
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8) FixedCs(instance, body_a, body_b, breakable, data);
    constraint->sub_7100F6A180(heap);
    return constraint;
}

void FixedCs::sub_7100F6D420(const sead::Matrix34f& a, const sead::Matrix34f& b,
                              const sead::Matrix34f& c) {
    hkTransform frame_a;
    hkTransform frame_b;
    hkTransform frame_c;
    toHkTransform(&frame_a, a);
    toHkTransform(&frame_b, b);
    toHkTransform(&frame_c, c);
    mData->sub_71015F3C84(frame_a, frame_b, frame_c);
}

void FixedCs::sub_7100F6D6D8(const sead::Matrix34f& mtx_a, const sead::Matrix34f& mtx_b) {
    hkTransform frame_a;
    hkTransform frame_b;
    toHkTransform(&frame_a, mtx_a);
    toHkTransform(&frame_b, mtx_b);
    mData->sub_71015F3F90(frame_a, frame_b);
}

}  // namespace ksys::phys

ksys::phys::FixedCs* sub_7100F6D358(sead::Heap* heap) {
    ksys::phys::FixedCs::Param param;
    return ksys::phys::FixedCs::make(param, heap);
}
