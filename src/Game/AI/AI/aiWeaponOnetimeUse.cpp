#include "Game/AI/AI/aiWeaponOnetimeUse.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

WeaponOnetimeUse::WeaponOnetimeUse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponOnetimeUse::~WeaponOnetimeUse() = default;

bool WeaponOnetimeUse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponOnetimeUse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponOnetimeUse::leave_() {
    sub_71005DB6D0(mActor, *mWeaponIdx_s);
}

void WeaponOnetimeUse::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
