#include "KingSystem/Physics/Constraint/physBAndSCs.h"
#include "KingSystem/Physics/Constraint/physBAndSLimitAngYCs.h"

namespace ksys::phys {

BAndSCs::~BAndSCs() = default;

u32 sub_7100F6B100(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x150;
}

BAndSLimitAngYCs::~BAndSLimitAngYCs() = default;

u32 sub_7100F6BD48(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

}  // namespace ksys::phys
