#include "Game/AI/Action/actionPlayerSleep.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSleep::PlayerSleep(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
}

void PlayerSleep::leave_() {}

void PlayerSleep::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    setFinished();
}

bool PlayerSleep::isChangeable() const {
    return false;
}

}  // namespace uking::action
