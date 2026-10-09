#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f70568 allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f6640.
class Unk_71024f6640 : public Constraint {
    SEAD_RTTI_OVERRIDE(Unk_71024f6640, Constraint)
public:
    ~Unk_71024f6640() override;

private:
    // The factory stores its library data pointer here; its interface is unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f6640, 0xc0);

}  // namespace ksys::phys
