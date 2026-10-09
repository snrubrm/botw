#include "KingSystem/Physics/Constraint/physRackAndPinionCs.h"
#include "KingSystem/Physics/Constraint/physUnk_71024f6640.h"

namespace ksys::phys {

RackAndPinionCs::~RackAndPinionCs() = default;
Unk_71024f6640::~Unk_71024f6640() = default;

u32 sub_7100F703FC(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1a0;
}

}  // namespace ksys::phys
