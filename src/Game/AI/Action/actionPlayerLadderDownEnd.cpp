#include "Game/AI/Action/actionPlayerLadderDownEnd.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLadderDownEnd::PlayerLadderDownEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderDownEnd::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    }
}

void PlayerLadderDownEnd::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderDownEnd::isChangeable() const {
    return true;
}

bool PlayerLadderDownEnd::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
