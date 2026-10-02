#include "Game/AI/AI/aiSpearWeaponSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

SpearWeaponSelect::SpearWeaponSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SpearWeaponSelect::~SpearWeaponSelect() = default;

bool SpearWeaponSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpearWeaponSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005DBB60(mActor, 0) == 2)
        changeChild("槍装備", params);
    else
        changeChild("槍以外", params);
}

void SpearWeaponSelect::calc_() {}

void SpearWeaponSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SpearWeaponSelect::loadParams_() {}

}  // namespace uking::ai
