#include "KingSystem/Physics/Constraint/physUnk_71024f6360.h"
#include <heap/seadHeap.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

// 0x71015f2fb8 / 0x71015f3384: the Havok cog-wheel data constructor and frame setter
// (declaration only; the library class name is unresolved).
void sub_71015F2FB8(hkpConstraintData* data);
void sub_71015F3384(hkpConstraintData* data, const hkVector4f& a, const hkVector4f& b,
                    const hkVector4f& c, const hkVector4f& d, f32 e, f32 f);

Unk_71024f6360::~Unk_71024f6360() = default;

// NON_MATCHING: the four frame vectors and the Constraint value temporary sit 0x10 lower on the
// stack (the call sequence and all field copies match).
Unk_71024f6360* Unk_71024f6360::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = static_cast<hkpConstraintData*>(heap->alloc(0xc0, 16));
    sub_71015F2FB8(data);
    hkVector4f frame_a;
    hkVector4f frame_b;
    hkVector4f frame_c;
    hkVector4f frame_d;
    toHkVec4(&frame_a, param._24);
    toHkVec4(&frame_b, param._3c);
    toHkVec4(&frame_c, param._30);
    toHkVec4(&frame_d, param._48);
    sub_71015F3384(data, frame_a, frame_b, frame_c, frame_d, param._54, param._58);
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8)
        Unk_71024f6360(instance, body_a, body_b, 7, breakable, data);
    constraint->sub_7100F6A180(heap);
    return constraint;
}

u32 sub_7100F6CC8C(bool breakable, bool) {
    return sub_7100F6ACF4(breakable) + 0x1a0;
}

}  // namespace ksys::phys
