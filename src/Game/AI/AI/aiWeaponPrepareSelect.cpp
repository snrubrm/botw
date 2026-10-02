#include "Game/AI/AI/aiWeaponPrepareSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

WeaponPrepareSelect::WeaponPrepareSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponPrepareSelect::~WeaponPrepareSelect() = default;

bool WeaponPrepareSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponPrepareSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005D8324(mActor, *mWeaponIdx_s))
        changeChild("完了", params);
    else
        changeChild("未完", params);
}

void WeaponPrepareSelect::calc_() {}

void WeaponPrepareSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponPrepareSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
