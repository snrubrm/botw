#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>

// 0x7101612d4c
void hkpRigidBody::setMass(hkReal mass) {
    getRigidMotion()->setMass(mass);
}

// 0x7101612d60
void hkpRigidBody::setMassInv(hkReal inverseMass) {
    getRigidMotion()->setMassInv(inverseMass);
}

// 0x7101612d74
void hkpRigidBody::setInertiaLocal(const hkMatrix3& inertia) {
    getRigidMotion()->setInertiaLocal(inertia);
}

// 0x7101612d88
void hkpRigidBody::setInertiaInvLocal(const hkMatrix3& inverseInertia) {
    getRigidMotion()->setInertiaInvLocal(inverseInertia);
}

// 0x7101612cbc
void hkpRigidBody::setPosition(const hkVector4& position) {
    getRigidMotion()->setPosition(position);
    updateBroadphaseAndResetCollisionInformationOfWarpedBody(this);
}

// 0x7101612cec
void hkpRigidBody::setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation) {
    getRigidMotion()->setPositionAndRotation(position, rotation);
    updateBroadphaseAndResetCollisionInformationOfWarpedBody(this);
}

// 0x7101612d1c
void hkpRigidBody::setTransform(const hkTransform& transform) {
    getRigidMotion()->setTransform(transform);
    updateBroadphaseAndResetCollisionInformationOfWarpedBody(this);
}

bool hkpRigidBody::isDeactivationEnabled() const {
    return getRigidMotion()->isDeactivationEnabled();
}

hkMotionState* hkpRigidBody::getMotionState() {
    return getRigidMotion()->getMotionState();
}
