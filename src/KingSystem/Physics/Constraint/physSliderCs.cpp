#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"
#include "KingSystem/Physics/Constraint/physSliderCs.h"
#include "KingSystem/Physics/Constraint/physUnk_71024f6778.h"

namespace ksys::phys {

SliderCs::~SliderCs() = default;
Unk_71024f6730::~Unk_71024f6730() = default;
Unk_71024f6778::~Unk_71024f6778() = default;

void Unk_71024f6778::sub_7100F719B4(Unk_71024f6778* object) {
    delete object;
}

void Unk_71024f6778::sub_7100F71A10() {
    _50 = 0.0f;
}

u32 sub_7100F70FB4(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x290 : 0x260);
}

}  // namespace ksys::phys
