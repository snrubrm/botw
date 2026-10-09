#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"
#include "KingSystem/Physics/Constraint/physSliderCs.h"
#include "KingSystem/Physics/Constraint/physUnk_71024f6778.h"

namespace ksys::phys {

SliderCs::~SliderCs() = default;
Unk_71024f6730::~Unk_71024f6730() = default;
Unk_71024f6778::~Unk_71024f6778() = default;

u32 sub_7100F70FB4(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x290 : 0x260);
}

}  // namespace ksys::phys
