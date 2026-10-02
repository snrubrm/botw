#include "Game/AI/Action/actionPlayerFrontRoll.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerFrontRoll::PlayerFrontRoll(const InitArg& arg) : PlayerAction(arg) {}

void PlayerFrontRoll::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerFrontRoll::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
}

void PlayerFrontRoll::loadParams_() {
    getStaticParam(&mEnergyDec_s, "EnergyDec");
    getStaticParam(&mSpeedDecByAngle_s, "SpeedDecByAngle");
}

void PlayerFrontRoll::calc_() {
    PlayerAction::calc_();
}

bool PlayerFrontRoll::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
