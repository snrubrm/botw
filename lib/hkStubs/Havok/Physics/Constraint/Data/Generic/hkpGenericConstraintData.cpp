#include <Havok/Physics/Constraint/Data/Generic/hkpGenericConstraintData.h>

hkpGenericConstraintData::~hkpGenericConstraintData() = default;

hkpConstraintData::ConstraintType hkpGenericConstraintData::getType() const {
    return CONSTRAINT_TYPE_CUSTOM;
}

void hkpGenericConstraintData::getConstraintInfo(ConstraintInfo& infoOut) const {
    getConstraintInfoUtil(&m_atoms.m_transforms, sizeof(m_atoms), infoOut);
}

hkBool hkpGenericConstraintData::isValid() const {
    return true;
}

void hkpGenericConstraintData::getRuntimeInfo(hkBool, RuntimeInfo&) const {}
