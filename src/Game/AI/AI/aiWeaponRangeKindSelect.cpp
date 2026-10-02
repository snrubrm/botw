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

void WeaponRangeKindSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponRangeKindSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
