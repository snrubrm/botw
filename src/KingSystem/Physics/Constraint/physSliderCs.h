#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f70d60 allocates 0x120, constructs Constraint, and
// installs the four-slot 0x71024f6700. Library data and frames stay opaque.
class SliderCs : public Constraint {
    SEAD_RTTI_OVERRIDE(SliderCs, Constraint)
public:
    ~SliderCs() override;

private:
    u8 _b8[0x120 - 0xb8];
};
KSYS_CHECK_SIZE_NX150(SliderCs, 0x120);

u32 sub_7100F70FB4(bool breakable, bool extra);

}  // namespace ksys::phys
