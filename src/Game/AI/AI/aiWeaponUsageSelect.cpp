#include "Game/AI/AI/aiWeaponUsageSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

WeaponUsageSelect::WeaponUsageSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WeaponUsageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponUsageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005D8B60(mActor)) {
        changeChild("素手", params);
        return;
    }

    switch (sub_71005DBB60(mActor, *mWeaponIdx_s)) {
    case 3:
        changeChild("遠隔武器", params);
        break;
    case 1:
        changeChild("近接重量武器", params);
        break;
    default:
        changeChild("近接軽量武器", params);
        break;
    }
}

void WeaponUsageSelect::calc_() {}

void WeaponUsageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponUsageSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
