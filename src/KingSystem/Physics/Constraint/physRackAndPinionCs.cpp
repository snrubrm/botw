#include "KingSystem/Physics/Constraint/physRackAndPinionCs.h"
#include "KingSystem/Physics/Constraint/physUnk_71024f6640.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

// 0x71015f7dd4 / 0x71015f815c: the Havok rack-and-pinion data constructor and
// frame setter (declaration only; the library class name is unresolved).
void sub_71015F7DD4(hkpConstraintData* data);
void sub_71015F815C(hkpConstraintData* data, const hkVector4f& a, const hkVector4f& b,
                    const hkVector4f& c, const hkVector4f& d, f32 e, bool f);

RackAndPinionCs::~RackAndPinionCs() = default;
Unk_71024f6640::~Unk_71024f6640() = default;

u32 sub_7100F703FC(bool breakable, bool) {
    return sub_7100F6ACF4(breakable) + 0x1a0;
}

RackAndPinionCs* RackAndPinionCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = static_cast<hkpConstraintData*>(heap->alloc(0xc0, 16));
    sub_71015F7DD4(data);
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8)
        RackAndPinionCs(instance, body_a, body_b, 8, breakable, data);
    constraint->sub_7100F6A180(heap);
    const f32 scalar = param._54;
    const bool flag = param._58;
    hkVector4f frame_a;
    hkVector4f frame_b;
    hkVector4f frame_c;
    hkVector4f frame_d;
    loadFromVec3(&frame_a, param._24);
    loadFromVec3(&frame_b, param._30);
    loadFromVec3(&frame_c, param._3c);
    loadFromVec3(&frame_d, param._48);
    sub_71015F815C(constraint->mData, frame_a, frame_b, frame_c, frame_d, scalar, flag);
    return constraint;
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
