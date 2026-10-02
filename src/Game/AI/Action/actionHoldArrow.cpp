#include "Game/AI/Action/actionHoldArrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

HoldArrow::HoldArrow(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void HoldArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void HoldArrow::leave_() {
    ActionWithPosAngReduce::leave_();
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
}

void HoldArrow::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void HoldArrow::calc_() {
    ActionWithPosAngReduce::calc_();
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
}

bool HoldArrow::isChangeable() const {
    return true;
}

}  // namespace uking::action
