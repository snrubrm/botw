#include "Game/AI/Action/actionPlayerSuperJumpCharge.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSuperJumpCharge::PlayerSuperJumpCharge(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperJumpCharge::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSuperJumpCharge::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1cbe = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
}

void PlayerSuperJumpCharge::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
}

void PlayerSuperJumpCharge::calc_() {
    PlayerAction::calc_();
}

bool PlayerSuperJumpCharge::isChangeable() const {
    return true;
}

}  // namespace uking::action
