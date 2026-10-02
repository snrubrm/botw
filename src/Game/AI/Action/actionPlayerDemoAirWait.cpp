#include "Game/AI/Action/actionPlayerDemoAirWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerDemoAirWait::PlayerDemoAirWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDemoAirWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDemoAirWait::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerDemoAirWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerDemoAirWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
