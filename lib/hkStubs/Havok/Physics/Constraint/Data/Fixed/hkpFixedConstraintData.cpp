#include <Havok/Physics/Constraint/Data/Fixed/hkpFixedConstraintData.h>

// 0x71015F3F90
void hkpFixedConstraintData::sub_71015F3F90(const hkTransform& bodyA, const hkTransform& bodyB) {
    m_atoms.m_transforms.m_transformA = bodyA;
    m_atoms.m_transforms.m_transformB = bodyB;
}
