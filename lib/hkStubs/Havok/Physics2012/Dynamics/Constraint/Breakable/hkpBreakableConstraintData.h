#pragma once

#include <Havok/Physics/Constraint/Data/hkpWrappedConstraintData.h>

// Reflection 16221a8 proves the wrapped parent and extent 0x50; game allocation
// f6c5fc independently requests 0x50 before invoking constructor 1618dc0.
class hkpBreakableConstraintData : public hkpWrappedConstraintData {
public:
    explicit hkpBreakableConstraintData(hkpConstraintData* constraintData);
    ~hkpBreakableConstraintData() override;
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    // Native 16194c8 returns the two reflected runtime sizes. Constructor/field
    // consumers do not dispatch through the unresolved base runtime slot.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

private:
    // Reflected atoms occupy +20..40; their contents are not modeled here.
    hkUint8 _20[0x20];

public:
    // Member records 25416f8/2541720 identify these two uint16 fields.
    hkUint16 m_childRuntimeSize;
    hkUint16 m_childNumSolverResults;
    // Record 2541748 names this hkReal at +44. Constructor 1618e00 sets it;
    // solver 1619064 loads it with +40, then extracts its float into s4.
    hkReal m_solverResultLimit;
    hkBool m_removeWhenBroken;
    hkBool m_revertBackVelocityOnBreak;
};

static_assert(sizeof(hkpBreakableConstraintData) == 0x50);
static_assert(offsetof(hkpBreakableConstraintData, m_solverResultLimit) == 0x44);
