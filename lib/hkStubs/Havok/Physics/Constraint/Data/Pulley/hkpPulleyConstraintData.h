#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// PulleyCs factory 0x7100f6f33c allocates 0x90 bytes and calls the constructor 0x71015f7640,
// which installs vtable 0x710253f7a8 and initialises both atoms.
class hkpPulleyConstraintData : public hkpConstraintData {
public:
    hkpPulleyConstraintData();
    ConstraintType getType() const override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

    struct Atoms {
        hkpSetLocalTranslationsConstraintAtom m_translations;
        hkpPulleyConstraintAtom m_pulley;
    };
    Atoms m_atoms;
};
static_assert(sizeof(hkpPulleyConstraintData) == 0x90);
static_assert(offsetof(hkpPulleyConstraintData, m_atoms) == 0x20);
