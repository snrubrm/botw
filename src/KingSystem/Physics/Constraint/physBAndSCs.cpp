#include "KingSystem/Physics/Constraint/physBAndSCs.h"
#include <Havok/Physics/Constraint/Data/BallAndSocket/hkpBallAndSocketConstraintData.h>
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/Constraint/physBAndSLimitAngYCs.h"

namespace ksys::phys {

BAndSCs::~BAndSCs() = default;

// NON_MATCHING: the compiler loads the vector components separately.
void BAndSCs::sub_7100F6B144(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b) {
    mData->sub_71015F47C8(toHkVec4(pivot_a), toHkVec4(pivot_b));
}

u32 sub_7100F6B100(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x150;
}

BAndSLimitAngYCs::~BAndSLimitAngYCs() = default;

u32 sub_7100F6BD48(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

}  // namespace ksys::phys
