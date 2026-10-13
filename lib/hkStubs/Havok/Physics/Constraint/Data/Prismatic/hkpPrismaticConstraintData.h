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

    // Full native 15F632C and independent SliderCs factory F70D60 pass
    // both pivots, both axes and both perpendicular axes by reference.
    void setInBodySpace(const hkVector4& pivotA, const hkVector4& pivotB,
                        const hkVector4& axisA, const hkVector4& axisB,
                        const hkVector4& perpendicularA, const hkVector4& perpendicularB);
    // Full map consumer D3E120 obtains the AllowRotation option before
    // forwarding it through SliderCs F7104C to native 15F5F54.
    void setAllowRotation(bool allowRotation);

    // The unresolved base runtime virtual domain is unchanged. Only the
    // established low slots and reflected data are declared here.
    struct Atoms {
        hkpSetLocalTransformsConstraintAtom m_transforms;
        // Reflected motor +90 and lin0/lin1 +D0/+E0 stay opaque.
        hkUint8 _90[0x20];
        hkpLinFrictionConstraintAtom m_friction;
        hkpAngConstraintAtom m_ang;
        hkUint8 _d0[0x20];
        hkpLinLimitConstraintAtom m_linLimit;
    };
    Atoms m_atoms;
};

static_assert(sizeof(hkpPrismaticConstraintData::Atoms) == 0x100);
static_assert(offsetof(hkpPrismaticConstraintData::Atoms, m_friction) == 0xb0);
static_assert(offsetof(hkpPrismaticConstraintData::Atoms, m_ang) == 0xc0);
static_assert(offsetof(hkpPrismaticConstraintData::Atoms, m_linLimit) == 0xf0);
static_assert(sizeof(hkpPrismaticConstraintData) == 0x120);
static_assert(offsetof(hkpPrismaticConstraintData, m_atoms) == 0x20);
