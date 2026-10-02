#include "Game/AI/Action/actionPlayerWallSlip.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWallSlip::PlayerWallSlip(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWallSlip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWallSlip::leave_() {}

void PlayerWallSlip::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerWallSlip::calc_() {
    PlayerAction::calc_();
}

bool PlayerWallSlip::isChangeable() const {
    return _1c;
}

bool PlayerWallSlip::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return true;
    return mActor->getASList()->x_4(0, 0);
}

}  // namespace uking::action
