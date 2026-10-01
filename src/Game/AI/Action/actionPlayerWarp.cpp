#include "Game/AI/Action/actionPlayerWarp.h"

namespace uking::action {

PlayerWarp::PlayerWarp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWarp::leave_() {}

void PlayerWarp::calc_() {
    PlayerAction::calc_();
}

bool PlayerWarp::isChangeable() const {
    return false;
}

}  // namespace uking::action
