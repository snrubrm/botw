#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpPulleyConstraintData;

namespace ksys::phys {

// Whole factory 0x7100f6f33c allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f6598.
class PulleyCs : public Constraint {
    SEAD_RTTI_OVERRIDE(PulleyCs, Constraint)
public:
    ~PulleyCs() override;

    // 0x7100f6f7f0 / 0x7100f6f7fc / 0x7100f6f808 (placeholder names): rope length and leverage of the
    // pulley data.
    void sub_7100F6F7F0(f32 length);
    void sub_7100F6F7FC(f32 leverage);
    f32 sub_7100F6F808() const;

private:
    hkpPulleyConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(PulleyCs, 0xc0);

u32 sub_7100F6F790(bool breakable, bool extra);

}  // namespace ksys::phys
