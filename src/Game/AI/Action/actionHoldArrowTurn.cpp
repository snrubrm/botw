#include "Game/AI/Action/actionHoldArrowTurn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HoldArrowTurn::HoldArrowTurn(const InitArg& arg) : TurnBase(arg) {}

void HoldArrowTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
    playAS("BowTurn", false, 0, 0, -1.0f);
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
}

void HoldArrowTurn::leave_() {
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
}

void HoldArrowTurn::loadParams_() {
    if (!mActor->getParam())
        return;
    TurnBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void HoldArrowTurn::calc_() {
    TurnBase::calc_();
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
}

}  // namespace uking::action
