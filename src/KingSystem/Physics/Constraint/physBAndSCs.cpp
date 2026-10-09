#include "KingSystem/Physics/Constraint/physBAndSCs.h"

namespace ksys::phys {

BAndSCs::~BAndSCs() = default;

u32 sub_7100F6B100(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x150;
}

}  // namespace ksys::phys
