#include <Havok/Physics/Constraint/Data/Hinge/hkpHingeConstraintData.h>

void hkpHingeConstraintData::setBreachImpulse(hkReal impulse) {
    m_atoms.m_ballSocket.m_breachImpulse = impulse;
}

hkReal hkpHingeConstraintData::getBreachImpulse() const {
    return m_atoms.m_ballSocket.m_breachImpulse;
}

void hkpHingeConstraintData::setBodyToNotify(int bodyIndex) {
    m_atoms.m_ballSocket.m_bodiesToNotify = 1 << bodyIndex;
}

hkUint8 hkpHingeConstraintData::getNotifiedBodyIndex() const {
    return m_atoms.m_ballSocket.m_bodiesToNotify >> 1;
}

void hkpHingeConstraintData::getConstraintInfo(ConstraintInfo& infoOut) const {
    getConstraintInfoUtil(&m_atoms.m_transforms, sizeof(m_atoms), infoOut);
}

hkpConstraintData::ConstraintType hkpHingeConstraintData::getType() const {
    return CONSTRAINT_TYPE_HINGE;
}

hkResult hkpHingeConstraintData::getInertiaStabilizationFactor(hkReal& factorOut) const {
    factorOut = m_atoms.m_ballSocket.m_inertiaStabilizationFactor;
    return HK_SUCCESS;
}

hkResult hkpHingeConstraintData::setInertiaStabilizationFactor(hkReal factor) {
    factor = factor < 0.0f ? 0.0f : (factor > 1.0f ? 1.0f : factor);
    m_atoms.m_ballSocket.m_inertiaStabilizationFactor = factor;
    return HK_SUCCESS;
}
