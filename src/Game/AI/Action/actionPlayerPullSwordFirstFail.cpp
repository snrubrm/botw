#include "Game/AI/Action/actionPlayerPullSwordFirstFail.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerPullSwordFirstFail::PlayerPullSwordFirstFail(const InitArg& arg) : PlayerAction(arg) {}

void PlayerPullSwordFirstFail::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    timer = ksys::Timer(*mFirstFailureWait_s, *mFirstFailureWait_s);
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
