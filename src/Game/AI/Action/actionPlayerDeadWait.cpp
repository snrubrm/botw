#include "Game/AI/Action/actionPlayerDeadWait.h"
#include "Game/gameUnk_71008ba8d8.h"

namespace uking::action {

PlayerDeadWait::PlayerDeadWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDeadWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDeadWait::leave_() {}

void PlayerDeadWait::calc_() {
    callPlayerGameOverDemo(mActor);
}

bool PlayerDeadWait::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
