#include "Game/AI/Action/actionPlayerShock.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerShock::PlayerShock(const InitArg& arg) : PlayerAction(arg) {}

void PlayerShock::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DamageShock", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
}

void PlayerShock::leave_() {}

void PlayerShock::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (!static_cast<ksys::act::Player*>(mActor)->_2558.isOn(0x20))
        setFinished();
}

bool PlayerShock::isChangeable() const {
    return false;
}

}  // namespace uking::action
