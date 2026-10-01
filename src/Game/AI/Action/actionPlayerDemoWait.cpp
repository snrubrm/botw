#include "Game/AI/Action/actionPlayerDemoWait.h"

namespace uking::action {

PlayerDemoWait::PlayerDemoWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDemoWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDemoWait::leave_() {}

void PlayerDemoWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerDemoWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
