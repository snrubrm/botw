#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f6f33c allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f6598.
class PulleyCs : public Constraint {
    SEAD_RTTI_OVERRIDE(PulleyCs, Constraint)
public:
    ~PulleyCs() override;
    // 223114 passes its independently typed PulleyCs receiver to these float queries.
    // The complete 12-byte bodies read the library data; declarations only.
    f32 sub_7100F71034();
    f32 sub_7100F71040();

private:
    // The factory stores its library data pointer here; its interface is unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(PulleyCs, 0xc0);

u32 sub_7100F6F790(bool breakable, bool extra);

}  // namespace ksys::phys
