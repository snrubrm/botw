#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpBallAndSocketConstraintData;

namespace ksys::phys {

// Whole factory 0x7100f6af10 allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f61f8.
class BAndSCs : public Constraint {
    SEAD_RTTI_OVERRIDE(BAndSCs, Constraint)
public:
    ~BAndSCs() override;

    void sub_7100F6B144(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b);

private:
    // Full factory and independent body-space setter use this same library owner.
    hkpBallAndSocketConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(BAndSCs, 0xc0);

u32 sub_7100F6B100(bool breakable);

}  // namespace ksys::phys
