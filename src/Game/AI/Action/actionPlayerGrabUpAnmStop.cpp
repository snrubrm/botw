#include "Game/AI/Action/actionPlayerGrabUpAnmStop.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGrabUpAnmStop::PlayerGrabUpAnmStop(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabUpAnmStop::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(1);
}

void PlayerGrabUpAnmStop::leave_() {}

void PlayerGrabUpAnmStop::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGrabUpAnmStop::isChangeable() const {
    return false;
}

}  // namespace uking::action
