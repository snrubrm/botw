#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Generic constraint data used by the motorcycle type-1 constraint. Native
// vtable 0x24f6480 (object vptr 0x24f6490), extent 0xc0, atoms 0xa0:
// transforms at +0x20 and a lin-friction atom at +0xb0. getType returns
// CONSTRAINT_TYPE_CUSTOM, getConstraintInfo uses atoms+0x20 size 0xa0 and
// isValid returns true.
class hkpGenericConstraintData : public hkpConstraintData {
public:
    HK_FORCE_INLINE hkpGenericConstraintData() { m_atoms.m_linFriction.m_isEnabled = true; }
    ~hkpGenericConstraintData() override;
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    // The unresolved base runtime slot order remains unchanged.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

    struct Atoms {
        hkpSetLocalTransformsConstraintAtom m_transforms;
        hkpLinFrictionConstraintAtom m_linFriction;
    };
    Atoms m_atoms;
};
static_assert(sizeof(hkpGenericConstraintData::Atoms) == 0xa0);
static_assert(offsetof(hkpGenericConstraintData::Atoms, m_linFriction) == 0x90);
static_assert(sizeof(hkpGenericConstraintData) == 0xc0);
static_assert(offsetof(hkpGenericConstraintData, m_atoms) == 0x20);
