#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Reflection 0x71017BA44C names the constraint-data parent, extent 0xe0,
// and aligned atoms at +0x20. FixedCs::make 0x7100F6D070 independently
// allocates 0xe0 and invokes constructor 0x71015F3BB8.
class hkpFixedConstraintData : public hkpConstraintData {
public:
    hkpFixedConstraintData();
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    // Declared for the native bool/output pair only. The unresolved base
    // runtime slot order is not repaired by this derived declaration.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

    // 0x71015F3F90 copies the complete body-space frames. Independent
    // callers 0x7100F6D070 and 0x7100F6D6D8 supply two hkTransform values.
    void sub_71015F3F90(const hkTransform& bodyA, const hkTransform& bodyB);

    struct Atoms {
        hkpSetLocalTransformsConstraintAtom m_transforms;
        hkpSetupStabilizationAtom m_setupStabilization;
        hkpBallSocketConstraintAtom m_ballSocket;
        hkp3dAngConstraintAtom m_ang;
    };

    Atoms m_atoms;
};

static_assert(sizeof(hkpFixedConstraintData::Atoms) == 0xc0);
static_assert(offsetof(hkpFixedConstraintData::Atoms, m_setupStabilization) == 0x90);
static_assert(offsetof(hkpFixedConstraintData::Atoms, m_ballSocket) == 0xa0);
static_assert(offsetof(hkpFixedConstraintData::Atoms, m_ang) == 0xb0);
static_assert(sizeof(hkpFixedConstraintData) == 0xe0);
static_assert(offsetof(hkpFixedConstraintData, m_atoms) == 0x20);
