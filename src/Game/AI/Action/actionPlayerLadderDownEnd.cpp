#include "Game/AI/Action/actionPlayerLadderDownEnd.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLadderDownEnd::PlayerLadderDownEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderDownEnd::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderDownEnd::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderDownEnd::isChangeable() const {
    return true;
}

bool PlayerLadderDownEnd::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
