#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpFixedRigidMotion.h>

// NON_MATCHING: implicit deleting destructor 0x71015fc02c moves the object argument earlier.

// 0x71015fbf5c
hkpFixedRigidMotion::hkpFixedRigidMotion(const hkVector4& position,
                                       const hkQuaternion& rotation)
    : hkpKeyframedRigidMotion(position, rotation) {
    m_type = MOTION_FIXED;
}

// 0x71015fbf94
void hkpFixedRigidMotion::setStepPosition(hkReal, hkReal) {}

// 0x71015fbf98
void hkpFixedRigidMotion::getPositionAndVelocities(hkpMotion* motionOut) {
    motionOut->m_motionState = m_motionState;
    motionOut->m_linearVelocity.setZero();
    motionOut->m_angularVelocity.setZero();
}

// 0x71015fc024
void hkpFixedRigidMotion::setLinearVelocity(const hkVector4&) {}

// 0x71015fc028
void hkpFixedRigidMotion::setAngularVelocity(const hkVector4&) {}
