#include "KingSystem/Physics/Constraint/physMotorcycleType1Cs.h"
#include "KingSystem/Physics/Constraint/physPulleyCs.h"

namespace ksys::phys {

// Adjacent constraint lifetime families at 0x7100f6ee80 and 0x7100f6f7c8.
MotorcycleType1Cs::~MotorcycleType1Cs() = default;
PulleyCs::~PulleyCs() = default;

u32 sub_7100F6F790(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x1a0 : 0x170);
}

}  // namespace ksys::phys
