#include <Havok/Physics2012/Dynamics/Motion/hkpMotion.h>
#include <Havok/Common/Base/Math/SweptTransform/hkSweptTransformfUtil.h>

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

// 0x7101606820
void hkpMotion::setMassInv(hkReal inverseMass) {
    m_inertiaAndMassInv(3) = inverseMass;
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

// 0x710160683c
void hkpMotion::setCenterOfMassInLocal(const hkVector4& centerOfMass) {
    hkSweptTransformUtil::sub_7101582B14(centerOfMass, m_motionState);
}

// 0x710160684c
void hkpMotion::setPosition(const hkVector4& position) {
    hkSweptTransformUtil::sub_7101582A2C(position, m_motionState);
}

// 0x710160685c
void hkpMotion::setRotation(const hkQuaternion& rotation) {
    hkSweptTransformUtil::sub_7101582A8C(rotation, m_motionState);
}

// 0x710160686c
void hkpMotion::setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation) {
    hkSweptTransformUtil::sub_71015828F0(position, rotation, m_motionState);
}

// 0x7101606880
void hkpMotion::setTransform(const hkTransform& transform) {
    hkSweptTransformUtil::sub_7101582984(transform, m_motionState);
}

// 0x7101606828
void hkpMotion::setMassInv(hkSimdRealParameter inverseMass) {
    m_inertiaAndMassInv.setW(inverseMass);
}

// 0x7101606890
void hkpMotion::approxTransformAt(hkTime time, hkTransform& transform) {
    m_motionState.getSweptTransform().sub_710177ED10(time, transform);
}
