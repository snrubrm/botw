#include "Game/AI/Action/actionPlayerSelfCamera.h"

namespace uking::action {

PlayerSelfCamera::PlayerSelfCamera(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSelfCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSelfCamera::leave_() {}

void PlayerSelfCamera::calc_() {
    PlayerAction::calc_();
}

bool PlayerSelfCamera::isChangeable() const {
    return true;
}

}  // namespace uking::action
