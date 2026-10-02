#include "Game/AI/Action/actionPlayerTwiceJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerTwiceJump::PlayerTwiceJump(const InitArg& arg) : PlayerFall(arg) {}

void PlayerTwiceJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerFall::enter_(params);
}

void PlayerTwiceJump::leave_() {}

void PlayerTwiceJump::loadParams_() {
    PlayerFall::loadParams_();
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerTwiceJump::calc_() {
    PlayerFall::calc_();
}

bool PlayerTwiceJump::isChangeable() const {
    return true;
}

bool PlayerTwiceJump::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
