#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Reflection 17BBFE0 names the parent, 0xe0 extent and atoms at +0x20.
// HingeCs factory F6D9DC independently allocates this extent and calls 15F68E8.
class hkpHingeConstraintData : public hkpConstraintData {
public:
    hkpHingeConstraintData();
    ~hkpHingeConstraintData() override;
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    void setBreachImpulse(hkReal impulse) override;
    hkReal getBreachImpulse() const override;
    void setBodyToNotify(int bodyIndex) override;
    hkUint8 getNotifiedBodyIndex() const override;
    hkResult getInertiaStabilizationFactor(hkReal& factorOut) const override;
    hkResult setInertiaStabilizationFactor(hkReal factor) override;
    // Native bool/output pair only; the unresolved base runtime slot order is unchanged.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

    // Full native 15F6B54 and independent HingeCs callers F6D9DC/F6DEAC
    // pass both pivots and both hinge axes in body space.
    void sub_71015F6B54(const hkVector4& pivotA, const hkVector4& pivotB,
                       const hkVector4& axisA, const hkVector4& axisB);

    struct Atoms {
        hkpSetLocalTransformsConstraintAtom m_transforms;
        hkpSetupStabilizationAtom m_setupStabilization;
        // Reflected 2dAng atom; its field meanings remain unrecovered.
        hkUint8 _a0[0x10];
        hkpBallSocketConstraintAtom m_ballSocket;
    };
    Atoms m_atoms;
};

static_assert(sizeof(hkpHingeConstraintData::Atoms) == 0xc0);
static_assert(offsetof(hkpHingeConstraintData::Atoms, m_setupStabilization) == 0x90);
static_assert(offsetof(hkpHingeConstraintData::Atoms, m_ballSocket) == 0xb0);
static_assert(sizeof(hkpHingeConstraintData) == 0xe0);
static_assert(offsetof(hkpHingeConstraintData, m_atoms) == 0x20);
