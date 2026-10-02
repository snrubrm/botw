#include "Game/AI/Action/actionPlayerSideStepLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSideStepLand::PlayerSideStepLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSideStepLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSideStepLand::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
}

void PlayerSideStepLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerSideStepLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
