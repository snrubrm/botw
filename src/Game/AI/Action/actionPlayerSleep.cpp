#include "Game/AI/Action/actionPlayerSleep.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSleep::PlayerSleep(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
}

void PlayerSleep::leave_() {}

void PlayerSleep::calc_() {
    PlayerAction::calc_();
}

bool PlayerSleep::isChangeable() const {
    return false;
}

}  // namespace uking::action
