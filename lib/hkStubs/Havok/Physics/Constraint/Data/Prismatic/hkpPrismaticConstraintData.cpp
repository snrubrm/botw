#include <Havok/Physics/Constraint/Data/Prismatic/hkpPrismaticConstraintData.h>

hkpConstraintData::ConstraintType hkpPrismaticConstraintData::getType() const {
    return CONSTRAINT_TYPE_PRISMATIC;
}

void hkpPrismaticConstraintData::getConstraintInfo(ConstraintInfo& infoOut) const {
    getConstraintInfoUtil(&m_atoms.m_transforms, sizeof(m_atoms), infoOut);
}

void hkpPrismaticConstraintData::getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const {
    infoOut = {0x58, 10};
}

void hkpPrismaticConstraintData::setInBodySpace(
    const hkVector4& pivotA, const hkVector4& pivotB, const hkVector4& axisA,
    const hkVector4& axisB, const hkVector4& perpendicularA, const hkVector4& perpendicularB) {
    auto& frameA = m_atoms.m_transforms.m_transformA;
    auto& frameB = m_atoms.m_transforms.m_transformB;
    frameA.getTranslation() = pivotA;
    frameB.getTranslation() = pivotB;
    frameA.getRotation().getColumn(0) = axisA;
    frameA.getRotation().getColumn(0).normalize<3>();
    frameA.getRotation().getColumn(1) = perpendicularA;
    frameA.getRotation().getColumn(1).normalize<3>();
    frameA.getRotation().getColumn(2).setCross(frameA.getRotation().getColumn(0),
                                             frameA.getRotation().getColumn(1));
    frameB.getRotation().getColumn(0) = axisB;
    frameB.getRotation().getColumn(0).normalize<3>();
    frameB.getRotation().getColumn(1) = perpendicularB;
    frameB.getRotation().getColumn(1).normalize<3>();
    frameB.getRotation().getColumn(2).setCross(frameB.getRotation().getColumn(0),
                                             frameB.getRotation().getColumn(1));
}

// NON_MATCHING: condition-test scheduling differs between constant loads.
void hkpPrismaticConstraintData::setAllowRotation(bool allowRotation) {
    m_atoms.m_ang.m_constrainedAxes[0] = allowRotation ? 1 : 0;
    m_atoms.m_ang.m_constrainedAxes[1] = allowRotation ? 2 : 1;
    m_atoms.m_ang.m_constrainedAxes[2] = allowRotation ? 0 : 2;
    m_atoms.m_ang.m_numConstrainedAxes = allowRotation ? 2 : 3;
}
