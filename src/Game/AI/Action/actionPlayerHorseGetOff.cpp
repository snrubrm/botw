#include "Game/AI/Action/actionPlayerHorseGetOff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerHorseGetOff::PlayerHorseGetOff(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHorseGetOff::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHorseGetOff::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerHorseGetOff::loadParams_() {
    getStaticParam(&mSideFallSpeed_s, "SideFallSpeed");
}

void PlayerHorseGetOff::calc_() {
    PlayerAction::calc_();
}

bool PlayerHorseGetOff::isChangeable() const {
    return false;
}

}  // namespace uking::action
