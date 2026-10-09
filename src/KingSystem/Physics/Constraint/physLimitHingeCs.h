#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// 0x7100f6e06c allocates 0xc0 and installs vtable 0x71024f63f0 after
// constructing Constraint. The table has RTTI queries and two destructors.
class LimitHingeCs : public Constraint {
    SEAD_RTTI_OVERRIDE(LimitHingeCs, Constraint)
public:
    ~LimitHingeCs() override;

private:
    // Factory and frame setter 0x7100f6e584 establish a pointer at this
    // offset; the library data interface remains unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(LimitHingeCs, 0xc0);

// The independent placement-link size query supplies false and true.
u32 sub_7100F6E2A0(bool breakable, bool extra);

}  // namespace ksys::phys
