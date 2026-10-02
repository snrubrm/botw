#include "Game/AI/Action/actionPlayerStepGuardJust.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerStepGuardJust::PlayerStepGuardJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStepGuardJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->x_23("GuardJust", false, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mJumpHeight_s *
                                   static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed());
    }
}

void PlayerStepGuardJust::leave_() {}

void PlayerStepGuardJust::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerStepGuardJust::calc_() {
    PlayerAction::calc_();
}

bool PlayerStepGuardJust::isChangeable() const {
    return _1c;
}

bool PlayerStepGuardJust::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
