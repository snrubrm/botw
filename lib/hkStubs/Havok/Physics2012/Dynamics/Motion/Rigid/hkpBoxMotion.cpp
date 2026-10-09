#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpBoxMotion.h>

// 0x710161ab70
void hkpBoxMotion::setMass(hkReal mass) {
    m_inertiaAndMassInv.setW(hkSimdReal(mass).reciprocal());
}

// 0x710161ab98
void hkpBoxMotion::setMass(hkSimdRealParameter mass) {
    m_inertiaAndMassInv.setW(mass.reciprocal());
}

// 0x710161acf0
void hkpBoxMotion::applyForce(hkReal deltaTime, const hkVector4& force) {
    hkVector4 impulse;
    impulse.setMul(hkSimdReal(deltaTime), force);
    m_linearVelocity.addMul(getMassInv(), impulse);
}

// 0x710161ad0c
void hkpBoxMotion::applyForce(hkReal deltaTime, const hkVector4& force, const hkVector4& point) {
    hkVector4 impulse;
    impulse.setMul(hkSimdReal(deltaTime), force);
    applyPointImpulse(impulse, point);
}

// 0x710161ad40
void hkpBoxMotion::applyTorque(hkReal deltaTime, const hkVector4& torque) {
    hkVector4 impulse;
    impulse.setMul(hkSimdReal(deltaTime), torque);
    applyAngularImpulse(impulse);
}
