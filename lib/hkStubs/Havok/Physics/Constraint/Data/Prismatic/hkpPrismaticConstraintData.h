#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Full reflection 17BBCA8 names the constraint-data parent, 0x120 extent,
// and 0x100-byte atoms at +0x20. SliderCs factory F70D60 independently
// allocates that extent and constructs the native data with 15F5E74.
class hkpPrismaticConstraintData : public hkpConstraintData {
public:
    hkpPrismaticConstraintData();
    ~hkpPrismaticConstraintData() override;
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;

    // The unresolved base runtime virtual domain is unchanged. Only the
    // established low slots and reflected data are declared here.
    struct Atoms {
        hkpSetLocalTransformsConstraintAtom m_transforms;
        // Complete reflected motor/friction/ang/lin0/lin1 records occupy
        // +90/+B0/+C0/+D0/+E0. Their storage remains opaque.
        hkUint8 _90[0x60];
        hkpLinLimitConstraintAtom m_linLimit;
    };
    Atoms m_atoms;
};

static_assert(sizeof(hkpPrismaticConstraintData::Atoms) == 0x100);
static_assert(offsetof(hkpPrismaticConstraintData::Atoms, m_linLimit) == 0xf0);
static_assert(sizeof(hkpPrismaticConstraintData) == 0x120);
static_assert(offsetof(hkpPrismaticConstraintData, m_atoms) == 0x20);
