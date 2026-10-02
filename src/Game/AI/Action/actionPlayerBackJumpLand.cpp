#include "Game/AI/Action/actionPlayerBackJumpLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerBackJumpLand::PlayerBackJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBackJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBackJumpLand::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
}

void PlayerBackJumpLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerBackJumpLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
