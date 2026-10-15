#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Complete reflection 17BBB0C and BAndSCs factory independently establish the70-byte owner.
class hkpBallAndSocketConstraintData : public hkpConstraintData {
public:
    hkpBallAndSocketConstraintData();
    ~hkpBallAndSocketConstraintData() override;
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    void setMaximumLinearImpulse(hkReal impulse) override;
    hkReal getMaximumLinearImpulse() const override;
    void setBreachImpulse(hkReal impulse) override;
    hkReal getBreachImpulse() const override;
    void setBodyToNotify(int bodyIndex) override;
    hkUint8 getNotifiedBodyIndex() const override;
    void setSolvingMethod(hkpConstraintAtom::SolvingMethod method) override;
    hkResult getInertiaStabilizationFactor(hkReal& factorOut) const override;
    hkResult setInertiaStabilizationFactor(hkReal factor) override;
    // The unresolved base runtime slot order remains unchanged.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

    // Native20-byte body-space setter; full BAndSCs factory and independent F6B144 call it.
    void sub_71015F47C8(const hkVector4& pivotA, const hkVector4& pivotB);

    struct Atoms {
        hkpSetLocalTranslationsConstraintAtom m_pivots;
        hkpSetupStabilizationAtom m_setupStabilization;
        hkpBallSocketConstraintAtom m_ballSocket;
    };
    Atoms m_atoms;
};
static_assert(sizeof(hkpBallAndSocketConstraintData::Atoms) == 0x50);
static_assert(offsetof(hkpBallAndSocketConstraintData::Atoms, m_setupStabilization) == 0x30);
static_assert(offsetof(hkpBallAndSocketConstraintData::Atoms, m_ballSocket) == 0x40);
static_assert(sizeof(hkpBallAndSocketConstraintData) == 0x70);
static_assert(offsetof(hkpBallAndSocketConstraintData, m_atoms) == 0x20);
