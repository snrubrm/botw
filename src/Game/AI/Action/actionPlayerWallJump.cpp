#include "Game/AI/Action/actionPlayerWallJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWallJump::PlayerWallJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWallJump::leave_() {}

void PlayerWallJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
}

void PlayerWallJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerWallJump::isChangeable() const {
    return true;
}

bool PlayerWallJump::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return true;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    return player->_1770.y < player->_2158 - 0.5f;
}

}  // namespace uking::action
