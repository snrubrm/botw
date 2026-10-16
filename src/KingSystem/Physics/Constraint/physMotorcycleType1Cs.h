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

    // 0x7100f6f1b4 (placeholder name): stores `value` at 0xb4 of the constraint data.
    void sub_7100F6F1B4(f32 value);

private:
    // Placeholder: the library constraint data the factory stores at _b8 (its class is unresolved).
    struct Data {
        u8 _0[0xb4];
        f32 _b4;
    };

    Data* mData;
};
KSYS_CHECK_SIZE_NX150(MotorcycleType1Cs, 0xc0);

}  // namespace ksys::phys
