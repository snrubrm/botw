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
