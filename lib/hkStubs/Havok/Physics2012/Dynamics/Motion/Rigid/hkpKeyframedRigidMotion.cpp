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
