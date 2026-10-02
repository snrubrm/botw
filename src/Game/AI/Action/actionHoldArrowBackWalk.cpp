#include "Game/AI/Action/actionHoldArrowBackWalk.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

HoldArrowBackWalk::HoldArrowBackWalk(const InitArg& arg) : BackWalkEx(arg) {}

void HoldArrowBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkEx::enter_(params);
    playAS("BowBackWalk", false, 0, 0, -1.0f);
    sub_71005D787C(mActor, *mHoldWeaponIdx_s, act::Unk_71002eda38(4));
}

void HoldArrowBackWalk::leave_() {
    BackWalkEx::leave_();
    sub_71005D787C(mActor, *mHoldWeaponIdx_s, act::Unk_71002eda38(5));
}

void HoldArrowBackWalk::loadParams_() {
    BackWalkEx::loadParams_();
    getStaticParam(&mHoldWeaponIdx_s, "HoldWeaponIdx");
}

void HoldArrowBackWalk::calc_() {
    BackWalkEx::calc_();
    sub_71005D787C(mActor, *mHoldWeaponIdx_s, act::Unk_71002eda38(4));
}

}  // namespace uking::action
