#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>

hkpConstraintData::ConstraintType hkpBreakableConstraintData::getType() const {
    return CONSTRAINT_TYPE_BREAKABLE;
}

void hkpBreakableConstraintData::getRuntimeInfo(hkBool, RuntimeInfo& infoOut) const {
    infoOut.m_numSolverResults = m_childNumSolverResults;
    infoOut.m_sizeOfExternalRuntime = m_childRuntimeSize + 0x34;
}
