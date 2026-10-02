#include "Game/AI/Action/actionPlayerWarp.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWarp::PlayerWarp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Warp", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
}

void PlayerWarp::leave_() {}

void PlayerWarp::calc_() {
    PlayerAction::calc_();
}

bool PlayerWarp::isChangeable() const {
    return false;
}

}  // namespace uking::action
