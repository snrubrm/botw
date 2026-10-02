#include "Game/AI/Action/actionPlayerSwimLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimLand::PlayerSwimLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0.3f;
    player->_20bc.prev_value = 0.3f;
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(15.0f, 15.0f);
}

void PlayerSwimLand::leave_() {}

void PlayerSwimLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimLand::isChangeable() const {
    return false;
}

}  // namespace uking::action
