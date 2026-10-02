#include "Game/AI/Action/actionPlayerShock.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerShock::PlayerShock(const InitArg& arg) : PlayerAction(arg) {}

void PlayerShock::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DamageShock", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
}

void PlayerShock::leave_() {}

void PlayerShock::calc_() {
    PlayerAction::calc_();
}

bool PlayerShock::isChangeable() const {
    return false;
}

}  // namespace uking::action
