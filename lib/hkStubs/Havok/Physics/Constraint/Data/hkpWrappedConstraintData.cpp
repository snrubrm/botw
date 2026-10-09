#include <Havok/Physics/Constraint/Data/hkpWrappedConstraintData.h>

void hkpWrappedConstraintData::getConstraintInfo(ConstraintInfo& infoOut) const {
    m_constraintData->getConstraintInfo(infoOut);
}

hkBool hkpWrappedConstraintData::isValid() const {
    return m_constraintData->isValid();
}
