#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"
#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

// 0x71015f1970 / 0x71015f1e18: the Havok limited-hinge data constructor and
// frame setter (declaration only; the library class name is unresolved).
hkpConstraintData* sub_71015F1970(void* data);
void sub_71015F1E18(void* data, const hkVector4f& a, const hkVector4f& b, const hkVector4f& c,
                    const hkVector4f& d, const hkVector4f& e, const hkVector4f& f);

LimitHingeCs::~LimitHingeCs() = default;

// NON_MATCHING: the data pointer and the breakable holder use the neighbouring registers and the
// six frame addresses are materialised one step later; the body and call sequence match.
LimitHingeCs* LimitHingeCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    void* storage = heap->alloc(sizeof(Data), 16);
    auto* data = sub_71015F1970(storage);
    auto* view = static_cast<Data*>(storage);
    view->mMaxAngle = param._70;
    view->mMinAngle = param._6c;
    view->mMaxFrictionTorque = param._74;
    view->mAngularLimitsTauFactor = param._78;
    hkVector4f frame_a;
    hkVector4f frame_b;
    hkVector4f frame_c;
    hkVector4f frame_d;
    hkVector4f frame_e;
    hkVector4f frame_f;
    loadFromVec3(&frame_a, param._24);
    loadFromVec3(&frame_b, param._30);
    loadFromVec3(&frame_c, param._3c);
    loadFromVec3(&frame_d, param._48);
    loadFromVec3(&frame_e, param._54);
    loadFromVec3(&frame_f, param._60);
    sub_71015F1E18(view, frame_a, frame_b, frame_c, frame_d, frame_e, frame_f);
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    auto* constraint = new (heap, 8)
        LimitHingeCs(instance, body_a, body_b, 4, breakable, view);
    if (param._20) {
        auto* item = new (heap, 8) Unk_71024f6420(constraint);
        constraint->_20 = item;
    }
    constraint->sub_7100F6A180(heap);
    return constraint;
}

void LimitHingeCs::sub_7100F6E584(const sead::Vector3f& a, const sead::Vector3f& b,
                                  const sead::Vector3f& c, const sead::Vector3f& d,
                                  const sead::Vector3f& e, const sead::Vector3f& f) {
    hkVector4f va;
    hkVector4f vb;
    hkVector4f vc;
    hkVector4f vd;
    hkVector4f ve;
    hkVector4f vf;
    loadFromVec3(&va, a);
    loadFromVec3(&vb, b);
    loadFromVec3(&vc, c);
    loadFromVec3(&vd, d);
    loadFromVec3(&ve, e);
    loadFromVec3(&vf, f);
    sub_71015F1E18(mData, va, vb, vc, vd, ve, vf);
}

void LimitHingeCs::sub_7100F6E300(f32 angle) {
    mData->mMinAngle = angle;
    mData->mMaxAngle = angle;
}

void LimitHingeCs::sub_7100F6E314(f32 min_angle, f32 max_angle) {
    mData->mMinAngle = min_angle;
    mData->mMaxAngle = max_angle;
}

void LimitHingeCs::sub_7100F6E328(f32 torque) {
    mData->mMaxFrictionTorque = torque;
}

void LimitHingeCs::sub_7100F6E334(f32 tau_factor) {
    mData->mAngularLimitsTauFactor = tau_factor;
}

f32 LimitHingeCs::sub_7100F6E340() const {
    return mData->mMaxAngle;
}

f32 LimitHingeCs::sub_7100F6E34C() const {
    return mData->mMinAngle;
}

f32 LimitHingeCs::sub_7100F6E358() const {
    return mData->mAngularLimitsTauFactor;
}
Unk_71024f6420::~Unk_71024f6420() = default;

u32 sub_7100F6E2A0(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x240 : 0x210);
}

}  // namespace ksys::phys
