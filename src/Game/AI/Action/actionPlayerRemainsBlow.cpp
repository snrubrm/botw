#include "Game/AI/Action/actionPlayerRemainsBlow.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerRemainsBlow::PlayerRemainsBlow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerRemainsBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerRemainsBlow::leave_() {}

void PlayerRemainsBlow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerRemainsBlow::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        setFinished();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerRemainsBlow::isChangeable() const {
    return false;
}

}  // namespace uking::action
