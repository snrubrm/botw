#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f6b918 allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f6310.
class BAndSLimitAngYCs : public Constraint {
    SEAD_RTTI_OVERRIDE(BAndSLimitAngYCs, Constraint)
public:
    ~BAndSLimitAngYCs() override;

private:
    // The factory stores its library data pointer here; its interface is unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(BAndSLimitAngYCs, 0xc0);

u32 sub_7100F6BD48(bool breakable);

}  // namespace ksys::phys
