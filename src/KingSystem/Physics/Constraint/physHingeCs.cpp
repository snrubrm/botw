#include "KingSystem/Physics/Constraint/physHingeCs.h"

namespace ksys::phys {

HingeCs::~HingeCs() = default;

u32 sub_7100F6DC48(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

}  // namespace ksys::phys
