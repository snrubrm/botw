#include <Havok/Physics2012/Dynamics/Motion/hkpMotion.h>

// NON_MATCHING: virtual target load and zero-mass branch placement.
// 0x710160677c
void hkpMotion::setMass(hkReal mass) {
    setMassInv(mass == 0.0f ? 0.0f : 1.0f / mass);
}

// NON_MATCHING: reciprocal and zero-mass selection scheduling.
// 0x71016067ec
hkReal hkpMotion::getMass() const {
    const hkSimdReal inverseMass = getMassInv();
    return inverseMass.isEqualZero() ? 0.0f : inverseMass.reciprocal().val();
}

// NON_MATCHING: vector component setter stores the complete vector.
// 0x7101606820
void hkpMotion::setMassInv(hkReal inverseMass) {
    m_inertiaAndMassInv.setW(inverseMass);
}

// 0x7101606964
void hkpMotion::setDeactivationClass(int deactivationClass) {
    m_motionState.m_deactivationClass = deactivationClass;
}

// 0x7101606898
void hkpMotion::setLinearVelocity(const hkVector4& velocity) {
    m_linearVelocity = velocity;
}

// 0x71016068a4
void hkpMotion::setAngularVelocity(const hkVector4& velocity) {
    m_angularVelocity = velocity;
}

// 0x71016068b0
void hkpMotion::applyLinearImpulse(const hkVector4& impulse) {
    m_linearVelocity.addMul(getMassInv(), impulse);
}

// 0x71016068c8
void hkpMotion::getMotionStateAndVelocitiesAndDeactivationType(hkpMotion* motionOut) {
    motionOut->m_motionState = m_motionState;
    motionOut->m_linearVelocity = m_linearVelocity;
    motionOut->m_angularVelocity = m_angularVelocity;
    motionOut->m_deactivationIntegrateCounter = m_deactivationIntegrateCounter;
}
