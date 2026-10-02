#include "Game/AI/Action/actionPlayerHangWallCatch.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerHangWallCatch::PlayerHangWallCatch(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHangWallCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHangWallCatch::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerHangWallCatch::calc_() {
    PlayerAction::calc_();
}

bool PlayerHangWallCatch::isChangeable() const {
    return false;
}

}  // namespace uking::action
