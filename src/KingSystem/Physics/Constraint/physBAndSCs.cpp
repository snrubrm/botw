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

// NON_MATCHING: vector loads and temporary constructor argument stack slots differ.
BAndSCs* BAndSCs::make(const Param& param, sead::Heap* heap) {
    auto* body_a = getPhysicsMemSysField190Or(param);
    auto* body_b = sub_7100F69FAC(param);
    auto* data = new (heap->alloc(sizeof(hkpBallAndSocketConstraintData), 16))
        hkpBallAndSocketConstraintData;
    hkVector4 pivot_a;
    hkVector4 pivot_b;
    loadFromVec3(&pivot_a, param.pivot_a);
    loadFromVec3(&pivot_b, param.pivot_b);
    data->sub_71015F47C8(pivot_a, pivot_b);
    const auto priority = param._18 ? hkpConstraintInstance::PRIORITY_TOI :
                                    hkpConstraintInstance::PRIORITY_PSI;
    auto* breakable = sub_7100F6ACA8(data, param, heap);
    hkpConstraintData* instance_data = data;
    if (breakable)
        instance_data = breakable->_8;
    auto* instance = new (heap->alloc(sizeof(hkpConstraintInstance), 16))
        hkpConstraintInstance(sub_7100F69FD8(), nullptr, instance_data, priority);
    hkArray<hkpConstraintInstance*> instances;
    instances.pushBack(instance);
    sub_71015FBE7C(instances, hkpConstraintAtom::METHOD_STABILIZED);
    auto* constraint = new (heap, 8) BAndSCs(instance, body_a, body_b, breakable, data);
    constraint->sub_7100F6A180(heap);
    return constraint;
}

// NON_MATCHING: the compiler loads the vector components separately.
void BAndSCs::sub_7100F6B144(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b) {
    mData->sub_71015F47C8(toHkVec4(pivot_a), toHkVec4(pivot_b));
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
