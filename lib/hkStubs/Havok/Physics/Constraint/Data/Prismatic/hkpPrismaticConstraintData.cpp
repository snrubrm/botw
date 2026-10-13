#include <Havok/Physics/Constraint/Data/Prismatic/hkpPrismaticConstraintData.h>

hkpConstraintData::ConstraintType hkpPrismaticConstraintData::getType() const {
    return CONSTRAINT_TYPE_PRISMATIC;
}

void hkpPrismaticConstraintData::getConstraintInfo(ConstraintInfo& infoOut) const {
    getConstraintInfoUtil(&m_atoms.m_transforms, sizeof(m_atoms), infoOut);
}
