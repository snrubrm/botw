#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpPrismaticConstraintData;

namespace ksys::phys {

// Whole factory 0x7100f70d60 allocates 0x120, constructs Constraint, and
// installs the four-slot 0x71024f6700. Library data and frames stay opaque.
class SliderCs : public Constraint {
    SEAD_RTTI_OVERRIDE(SliderCs, Constraint)
public:
    ~SliderCs() override;
    void setMinMaxLimit(f32 min, f32 max);
    // 223114 uses SliderCs's typeInfo at 0x71025b5228 before these data queries.
    f32 sub_7100F71034();
    f32 sub_7100F71040();

private:
    // Factory 0x7100f70d60 stores the independently constructed prismatic data here.
    hkpPrismaticConstraintData* mData;
    u8 _c0[0x120 - 0xc0];
};
KSYS_CHECK_SIZE_NX150(SliderCs, 0x120);

u32 sub_7100F70FB4(bool breakable, bool extra);

}  // namespace ksys::phys
