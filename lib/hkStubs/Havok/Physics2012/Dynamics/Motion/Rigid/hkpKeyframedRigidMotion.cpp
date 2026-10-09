#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>

// 0x7101612f18
void hkpKeyframedRigidMotion::setMass(hkReal) {}

// 0x7101612f1c
void hkpKeyframedRigidMotion::setMass(hkSimdRealParameter) {}

// 0x7101612f20
void hkpKeyframedRigidMotion::setMassInv(hkReal) {}

// 0x7101612f24
void hkpKeyframedRigidMotion::setMassInv(hkSimdRealParameter) {}

// 0x7101612f28
void hkpKeyframedRigidMotion::getInertiaLocal(hkMatrix3& inertia) const {
    inertia.setZero();
}

// 0x7101612f38
void hkpKeyframedRigidMotion::getInertiaWorld(hkMatrix3& inertia) const {
    inertia.setZero();
}

// 0x7101612f48
void hkpKeyframedRigidMotion::setInertiaLocal(const hkMatrix3&) {}

// 0x7101612f4c
void hkpKeyframedRigidMotion::setInertiaInvLocal(const hkMatrix3&) {}

// 0x7101612f50
void hkpKeyframedRigidMotion::getInertiaInvLocal(hkMatrix3& inertia) const {
    inertia.setZero();
}

// 0x7101612f60
void hkpKeyframedRigidMotion::getInertiaInvWorld(hkMatrix3& inertia) const {
    inertia.setZero();
}

// 0x7101612f70
void hkpKeyframedRigidMotion::applyLinearImpulse(const hkVector4&) {}

// 0x7101612f74
void hkpKeyframedRigidMotion::applyPointImpulse(const hkVector4&, const hkVector4&) {}

// 0x7101612f78
void hkpKeyframedRigidMotion::applyAngularImpulse(const hkVector4&) {}

// 0x7101612f7c
void hkpKeyframedRigidMotion::applyForce(hkReal, const hkVector4&) {}

// 0x7101612f80
void hkpKeyframedRigidMotion::applyForce(hkReal, const hkVector4&, const hkVector4&) {}

// 0x7101612f84
void hkpKeyframedRigidMotion::applyTorque(hkReal, const hkVector4&) {}

// 0x7101612f88
void hkpKeyframedRigidMotion::setStepPosition(hkReal, hkReal) {}

// NON_MATCHING: existing reference-count atomic retry branch layout.
// 0x7101612f8c
void hkpKeyframedRigidMotion::setStoredMotion(hkpMaxSizeMotion* savedMotion) {
    if (savedMotion)
        savedMotion->addReference();
    if (m_savedMotion)
        m_savedMotion->removeReference();
    m_savedMotion = savedMotion;
}

// 0x710161304c
void hkpKeyframedRigidMotion::getProjectedPointVelocity(const hkVector4& point,
                                                      const hkVector4& normal,
                                                      hkReal& velocityOut,
                                                      hkReal& inverseVirtualMassOut) const {
    hkVector4 relativePosition;
    relativePosition.setSub(point, getCenterOfMassInWorld());
    hkVector4 angularDirection;
    angularDirection.setCross(normal, relativePosition);
    velocityOut = (angularDirection.dot<3>(m_angularVelocity) +
                   normal.dot<3>(m_linearVelocity)).val();
    inverseVirtualMassOut = 0.0f;
}

// NON_MATCHING: paired velocity loads, reduction scheduling and zero store.
// 0x71016130d0
void hkpKeyframedRigidMotion::getProjectedPointVelocitySimd(const hkVector4& point,
                                                          const hkVector4& normal,
                                                          hkSimdReal& velocityOut,
                                                          hkSimdReal& inverseVirtualMassOut) const {
    hkVector4 relativePosition;
    relativePosition.setSub(point, getCenterOfMassInWorld());
    hkVector4 angularDirection;
    angularDirection.setCross(normal, relativePosition);
    velocityOut = angularDirection.dot<3>(m_angularVelocity) + normal.dot<3>(m_linearVelocity);
    inverseVirtualMassOut = hkSimdReal(0.0f);
}
