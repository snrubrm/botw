#include "Game/AI/Action/actionPlayerHellStartWait.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

PlayerHellStartWait::PlayerHellStartWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerHellStartWait::~PlayerHellStartWait() = default;

void PlayerHellStartWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHellStartWait::leave_() {
    ksys::evt::Manager::instance()->_1d2f4 &= ~1u;
}

void PlayerHellStartWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerHellStartWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
