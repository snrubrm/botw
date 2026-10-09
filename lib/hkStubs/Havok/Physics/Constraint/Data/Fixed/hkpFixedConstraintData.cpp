#include <Havok/Physics/Constraint/Data/Fixed/hkpFixedConstraintData.h>

// 0x71015F3F90
void hkpFixedConstraintData::sub_71015F3F90(const hkTransform& bodyA, const hkTransform& bodyB) {
    m_atoms.m_transforms.m_transformA = bodyA;
    m_atoms.m_transforms.m_transformB = bodyB;
}

// 0x71015F3FD4
void hkpFixedConstraintData::setMaximumLinearImpulse(hkReal maxLinearImpulse) {
    m_atoms.m_setupStabilization.m_maxLinImpulse = maxLinearImpulse;
    m_atoms.m_ballSocket.m_enableLinearImpulseLimit = maxLinearImpulse < HK_REAL_MAX;
}

// 0x71015F3FF0
void hkpFixedConstraintData::setMaximumAngularImpulse(hkReal maxAngularImpulse) {
    m_atoms.m_setupStabilization.m_maxAngImpulse = maxAngularImpulse;
}

// 0x71015F3FF8
hkReal hkpFixedConstraintData::getMaximumLinearImpulse() const {
    return m_atoms.m_setupStabilization.m_maxLinImpulse;
}

// 0x71015F4000
hkReal hkpFixedConstraintData::getMaximumAngularImpulse() const {
    return m_atoms.m_setupStabilization.m_maxAngImpulse;
}

// 0x71015F4008
void hkpFixedConstraintData::setBodyToNotify(int bodyIndex) {
    m_atoms.m_ballSocket.m_bodiesToNotify = 1 << bodyIndex;
}

// 0x71015F4018
hkUint8 hkpFixedConstraintData::getNotifiedBodyIndex() const {
    return m_atoms.m_ballSocket.m_bodiesToNotify >> 1;
}

// 0x71015F406C
// NON_MATCHING: the second condition is materialized instead of branching to the shared return.
hkBool hkpFixedConstraintData::isValid() const {
    return m_atoms.m_ballSocket.m_solvingMethod != hkpConstraintAtom::METHOD_STABILIZED ||
           m_atoms.m_setupStabilization.m_enabled;
}

// 0x71015F4094
// NON_MATCHING: the compiler merges the two cases' stores into a common block.
void hkpFixedConstraintData::setSolvingMethod(hkpConstraintAtom::SolvingMethod method) {
    switch (method) {
    case hkpConstraintAtom::METHOD_STABILIZED:
        m_atoms.m_setupStabilization.m_enabled = true;
        m_atoms.m_ballSocket.m_solvingMethod = hkpConstraintAtom::METHOD_STABILIZED;
        break;
    case hkpConstraintAtom::METHOD_OLD:
        m_atoms.m_setupStabilization.m_enabled = false;
        m_atoms.m_ballSocket.m_solvingMethod = hkpConstraintAtom::METHOD_OLD;
        break;
    }
}

// 0x71015F40C0
hkResult hkpFixedConstraintData::getInertiaStabilizationFactor(hkReal& factorOut) const {
    factorOut = m_atoms.m_ballSocket.m_inertiaStabilizationFactor;
    return HK_SUCCESS;
}
