#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"

namespace ksys::phys {

LimitHingeCs::~LimitHingeCs() = default;

u32 sub_7100F6E2A0(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x240 : 0x210);
}

}  // namespace ksys::phys
