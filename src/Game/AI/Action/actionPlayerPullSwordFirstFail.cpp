#include "Game/AI/Action/actionPlayerPullSwordFirstFail.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerPullSwordFirstFail::PlayerPullSwordFirstFail(const InitArg& arg) : PlayerAction(arg) {}

void PlayerPullSwordFirstFail::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerPullSwordFirstFail::leave_() {
    mActor->getASList()->sub_710115C11C();
}

void PlayerPullSwordFirstFail::loadParams_() {
    getStaticParam(&mFirstFailureWait_s, "FirstFailureWait");
}

void PlayerPullSwordFirstFail::calc_() {
    PlayerAction::calc_();
}

bool PlayerPullSwordFirstFail::isChangeable() const {
    return false;
}

}  // namespace uking::action
