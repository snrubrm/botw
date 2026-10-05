#include "Game/AI/AI/aiWeaponRangeKindSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

WeaponRangeKindSelect::WeaponRangeKindSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WeaponRangeKindSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponRangeKindSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005D8B60(mActor)) {
        changeChild("素手", params);
        return;
    }

    const s32 type = sub_71005DBB60(mActor, *mWeaponIdx_s);
    if (type == -1)
        changeChild("非武器装備", params);
    else if (type == 3)
        changeChild("遠隔武器", params);
    else
        changeChild("近接武器", params);
}

// NON_MATCHING: the compiler reorders the weapon-kind comparisons and their child branches.
void WeaponRangeKindSelect::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;

    if (sub_71005DBB60(mActor, *mWeaponIdx_s) == -1 && sub_71005DB96C(mActor) < 0) {
        if (!isCurrentChild("素手"))
            changeChild("素手");
        return;
    }

    const s32 type = sub_71005DBB60(mActor, *mWeaponIdx_s);
    if (type == -1) {
        if (!isCurrentChild("非武器装備"))
            changeChild("非武器装備");
    } else if (type == 3) {
        if (!isCurrentChild("遠隔武器"))
            changeChild("遠隔武器");
    } else if (!isCurrentChild("近接武器")) {
        changeChild("近接武器");
    }
}

void WeaponRangeKindSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponRangeKindSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
