#include "KingSystem/Physics/Constraint/physRackAndPinionCs.h"

namespace ksys::phys {

RackAndPinionCs::~RackAndPinionCs() = default;

u32 sub_7100F703FC(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1a0;
}

}  // namespace ksys::phys
