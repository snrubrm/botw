#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f6ecec allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f6568.
class MotorcycleType1Cs : public Constraint {
    SEAD_RTTI_OVERRIDE(MotorcycleType1Cs, Constraint)
public:
    ~MotorcycleType1Cs() override;

private:
    // The factory stores its library data pointer here; its interface is unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(MotorcycleType1Cs, 0xc0);

}  // namespace ksys::phys
