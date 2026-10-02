#include "Game/AI/Action/actionHoldArrowWalk.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

HoldArrowWalk::HoldArrowWalk(const InitArg& arg) : MoveBase(arg) {}

HoldArrowWalk::~HoldArrowWalk() = default;

void HoldArrowWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
    playAS("BowBattleWalk", false, 0, 0, -1.0f);
    sub_71005D787C(mActor, *mHoldWeaponIdx_s, act::Unk_71002eda38(4));
}

void HoldArrowWalk::leave_() {
    MoveBase::leave_();
    sub_71005D787C(mActor, *mHoldWeaponIdx_s, act::Unk_71002eda38(5));
}

void HoldArrowWalk::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mHoldWeaponIdx_s, "HoldWeaponIdx");
}

void HoldArrowWalk::calc_() {
    MoveBase::calc_();
    sub_71005D787C(mActor, *mHoldWeaponIdx_s, act::Unk_71002eda38(4));
}

f32 HoldArrowWalk::m34() {
    return 0.5f;
}

}  // namespace uking::action
