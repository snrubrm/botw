#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Reflection 0x71017BEBB8 names the parent and extent 0x130; the atoms class
// has extent 0x110 with transforms/setupStabilization/angMotor/
// angFriction/angLimit/2dAng/ballSocket at 0/0x90/0xa0/0xc0/0xd0/0xf0/0x100.
// LimitHingeCs::make 0x7100F6E06C independently allocates 0x130, calls
// constructor 0x71015F1970 and frame setter 0x71015F1E18.
class hkpLimitedHingeConstraintData : public hkpConstraintData {
public:
    hkpLimitedHingeConstraintData();
    ~hkpLimitedHingeConstraintData() override;
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    // The unresolved base runtime slot order remains unchanged.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

    // 0x71015F1E18: builds both local frames from two axes per body and stores
    // both body-space pivots. LimitHingeCs::make passes six vectors.
    void sub_71015F1E18(const hkVector4& pivotA, const hkVector4& pivotB,
                        const hkVector4& axisA, const hkVector4& axisB,
                        const hkVector4& axisA2, const hkVector4& axisB2);

    struct Atoms {
        hkpSetLocalTransformsConstraintAtom m_transforms;
        hkpSetupStabilizationAtom m_setupStabilization;
        hkpAngMotorConstraintAtom m_angMotor;
        hkpAngFrictionConstraintAtom m_angFriction;
        hkpAngLimitConstraintAtom m_angLimit;
        hkp2dAngConstraintAtom m_2dAng;
        hkpBallSocketConstraintAtom m_ballSocket;
    };
    Atoms m_atoms;
};
static_assert(sizeof(hkpLimitedHingeConstraintData::Atoms) == 0x110);
static_assert(offsetof(hkpLimitedHingeConstraintData::Atoms, m_setupStabilization) == 0x90);
static_assert(offsetof(hkpLimitedHingeConstraintData::Atoms, m_angMotor) == 0xa0);
static_assert(offsetof(hkpLimitedHingeConstraintData::Atoms, m_angFriction) == 0xc0);
static_assert(offsetof(hkpLimitedHingeConstraintData::Atoms, m_angLimit) == 0xd0);
static_assert(offsetof(hkpLimitedHingeConstraintData::Atoms, m_2dAng) == 0xf0);
static_assert(offsetof(hkpLimitedHingeConstraintData::Atoms, m_ballSocket) == 0x100);
static_assert(sizeof(hkpLimitedHingeConstraintData) == 0x130);
static_assert(offsetof(hkpLimitedHingeConstraintData, m_atoms) == 0x20);
