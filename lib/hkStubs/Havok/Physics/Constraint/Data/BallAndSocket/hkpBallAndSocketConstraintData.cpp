#include <Havok/Physics/Constraint/Data/BallAndSocket/hkpBallAndSocketConstraintData.h>

void hkpBallAndSocketConstraintData::setInWorldSpace(const hkTransform& bodyATransform,
                                                     const hkTransform& bodyBTransform,
                                                     const hkVector4& pivot) {
    m_atoms.m_pivots.m_translationA._setTransformedInversePos(bodyATransform, pivot);
    m_atoms.m_pivots.m_translationB._setTransformedInversePos(bodyBTransform, pivot);
}

void hkpBallAndSocketConstraintData::sub_71015F47C8(const hkVector4& pivotA,
                                                 const hkVector4& pivotB) {
    m_atoms.m_pivots.m_translationA = pivotA;
    m_atoms.m_pivots.m_translationB = pivotB;
}

void hkpBallAndSocketConstraintData::setBreachImpulse(hkReal impulse) {
    m_atoms.m_ballSocket.m_breachImpulse = impulse;
}

hkReal hkpBallAndSocketConstraintData::getBreachImpulse() const {
    return m_atoms.m_ballSocket.m_breachImpulse;
}

void hkpBallAndSocketConstraintData::setMaximumLinearImpulse(hkReal impulse) {
    m_atoms.m_setupStabilization.m_maxLinImpulse = impulse;
    m_atoms.m_ballSocket.m_enableLinearImpulseLimit = impulse < HK_REAL_MAX;
}

hkReal hkpBallAndSocketConstraintData::getMaximumLinearImpulse() const {
    return m_atoms.m_setupStabilization.m_maxLinImpulse;
}

void hkpBallAndSocketConstraintData::setBodyToNotify(int bodyIndex) {
    m_atoms.m_ballSocket.m_bodiesToNotify = 1 << bodyIndex;
}

hkUint8 hkpBallAndSocketConstraintData::getNotifiedBodyIndex() const {
    return m_atoms.m_ballSocket.m_bodiesToNotify >> 1;
}

void hkpBallAndSocketConstraintData::getConstraintInfo(ConstraintInfo& infoOut) const {
    getConstraintInfoUtil(&m_atoms.m_pivots, sizeof(m_atoms), infoOut);
}

hkpConstraintData::ConstraintType hkpBallAndSocketConstraintData::getType() const {
    return CONSTRAINT_TYPE_BALLANDSOCKET;
}

hkResult hkpBallAndSocketConstraintData::getInertiaStabilizationFactor(hkReal& factorOut) const {
    factorOut = m_atoms.m_ballSocket.m_inertiaStabilizationFactor;
    return HK_SUCCESS;
}

hkResult hkpBallAndSocketConstraintData::setInertiaStabilizationFactor(hkReal factor) {
    factor = factor < 0.0f ? 0.0f : (factor > 1.0f ? 1.0f : factor);
    m_atoms.m_ballSocket.m_inertiaStabilizationFactor = factor;
    return HK_SUCCESS;
}
