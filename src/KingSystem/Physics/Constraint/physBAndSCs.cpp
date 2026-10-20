#include "KingSystem/Physics/Constraint/physBAndSCs.h"
#include <Havok/Physics/Constraint/Data/BallAndSocket/hkpBallAndSocketConstraintData.h>
#include <Havok/Physics/Constraint/Util/hkpConstraintUtils.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <heap/seadHeap.h>
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/Constraint/physBAndSLimitAngYCs.h"

namespace ksys::phys {

BAndSCs::~BAndSCs() = default;

BAndSCs* BAndSCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpBallAndSocketConstraintData), 16))
        hkpBallAndSocketConstraintData;
    data->sub_71015F47C8(toHkVec4(param.pivot_a), toHkVec4(param.pivot_b));
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    hkArray<hkpConstraintInstance*> instances;
    instances.setSize(1);
    instances[0] = instance;
    sub_71015FBE7C(instances, hkpConstraintAtom::METHOD_STABILIZED);
    auto* constraint = new (heap, 8) BAndSCs(instance, body_a, body_b, breakable, data);
    constraint->sub_7100F6A180(heap);
    return constraint;
}

void BAndSCs::sub_7100F6B144(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b) {
    hkVector4 pivot_a_hk;
    hkVector4 pivot_b_hk;
    loadFromVec3(&pivot_a_hk, pivot_a);
    loadFromVec3(&pivot_b_hk, pivot_b);
    mData->sub_71015F47C8(pivot_a_hk, pivot_b_hk);
}

void BAndSCs::sub_7100F6B198(const sead::Matrix34f& body_a_mtx,
                             const sead::Matrix34f& body_b_mtx, const sead::Vector3f& pivot) {
    hkTransform transform_a;
    toHkTransform(&transform_a, body_a_mtx);
    hkTransform transform_b;
    toHkTransform(&transform_b, body_b_mtx);
    hkVector4 pivot_hk;
    loadFromVec3(&pivot_hk, pivot);
    mData->setInWorldSpace(transform_a, transform_b, pivot_hk);
}

void BAndSCs::sub_7100F6B394(sead::Vector3f* pivot_a, sead::Vector3f* pivot_b) const {
    storeToVec3(pivot_a, mData->m_atoms.m_pivots.m_translationA);
    storeToVec3(pivot_b, mData->m_atoms.m_pivots.m_translationB);
}

void BAndSLimitAngYCs::sub_7100F6BD8C(const sead::Matrix34f& a,
                                    const sead::Matrix34f& b) {
    hkTransform transform_a;
    hkTransform transform_b;
    toHkTransform(&transform_a, a);
    toHkTransform(&transform_b, b);
    auto& transforms = mData->m_transforms;
    transforms.m_transformA = transform_a;
    transforms.m_transformB = transform_b;
}

// NON_MATCHING: the two quaternion temporaries occupy separate stack slots.
void BAndSLimitAngYCs::sub_7100F6C280(sead::Matrix34f* a, sead::Matrix34f* b) const {
    const auto& transform_a = mData->m_transforms.m_transformA;
    hkQuaternion rotation_a;
    rotation_a.set(transform_a.getRotation());
    a->makeQT(toQuat(rotation_a), toVec3(transform_a.getTranslation()));
    const auto& transform_b = mData->m_transforms.m_transformB;
    hkQuaternion rotation_b;
    rotation_b.set(transform_b.getRotation());
    b->makeQT(toQuat(rotation_b), toVec3(transform_b.getTranslation()));
}

u32 sub_7100F6B100(bool breakable, bool) {
    return sub_7100F6ACF4(breakable) + 0x150;
}

BAndSLimitAngYCs::~BAndSLimitAngYCs() = default;

void BAndSLimitAngYCs::sub_7100F6C254(sead::Vector3f* pivot_a, sead::Vector3f* pivot_b) const {
    storeToVec3(pivot_a, mData->m_transforms.m_transformA.getTranslation());
    storeToVec3(pivot_b, mData->m_transforms.m_transformB.getTranslation());
}

u32 sub_7100F6BD48(bool breakable, bool) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

}  // namespace ksys::phys
