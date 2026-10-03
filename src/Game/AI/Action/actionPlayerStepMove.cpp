#include "Game/AI/Action/actionPlayerStepMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerStepMove::PlayerStepMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x8);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Stair", true, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        controller->sub_7100F631E0(false);
    }
}

void PlayerStepMove::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F631E0(true);
    }
}

void PlayerStepMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerStepMove::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
