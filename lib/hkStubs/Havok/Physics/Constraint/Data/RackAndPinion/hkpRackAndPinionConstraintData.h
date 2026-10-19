#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Reflection 0x71017BBE50 names the parent and extent 0xc0; its atoms class
// (0x71017BBE50/0x71017BE10) has extent 0xa0 with transforms at 0 and
// rackAndPinion at 0x90. RackAndPinionCs::make 0x7100F70248 independently
// allocates 0xc0, calls constructor 0x71015F7DD4 and setter 0x71015F815C.
class hkpRackAndPinionConstraintData : public hkpConstraintData {
public:
    hkpRackAndPinionConstraintData();
    ~hkpRackAndPinionConstraintData() override;
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    // The unresolved base runtime slot order remains unchanged.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

    // 0x71015F815C: builds both local frames from two axes per body and stores
    // the pitch/screw flag in the rack-and-pinion atom.
    void sub_71015F815C(const hkVector4& pivotA, const hkVector4& pivotB,
                        const hkVector4& axisA, const hkVector4& axisB, bool isScrew,
                        hkReal pinionRadiusOrScrewPitch);

    struct Atoms {
        hkpSetLocalTransformsConstraintAtom m_transforms;
        hkpRackAndPinionConstraintAtom m_rackAndPinion;
    };
    Atoms m_atoms;
};
static_assert(sizeof(hkpRackAndPinionConstraintData::Atoms) == 0xa0);
static_assert(offsetof(hkpRackAndPinionConstraintData::Atoms, m_rackAndPinion) == 0x90);
static_assert(sizeof(hkpRackAndPinionConstraintData) == 0xc0);
static_assert(offsetof(hkpRackAndPinionConstraintData, m_atoms) == 0x20);
