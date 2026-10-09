#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f70248 allocates 0xc0 and installs the four-slot
// vtable 0x71024f6610 after calling Constraint's constructor.
class RackAndPinionCs : public Constraint {
    SEAD_RTTI_OVERRIDE(RackAndPinionCs, Constraint)
public:
    ~RackAndPinionCs() override;

private:
    // The factory stores its library data pointer here; that interface
    // remains unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(RackAndPinionCs, 0xc0);

u32 sub_7100F703FC(bool breakable);

}  // namespace ksys::phys
