#include "Game/AI/Action/actionPlayerGuardJustFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGuardJustFall::PlayerGuardJustFall(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardJustFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GuardJust", true, -1.0f);
}

void PlayerGuardJustFall::leave_() {}

void PlayerGuardJustFall::calc_() {
    m32();
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        setFinished();
}

bool PlayerGuardJustFall::isChangeable() const {
    return false;
}

}  // namespace uking::action
