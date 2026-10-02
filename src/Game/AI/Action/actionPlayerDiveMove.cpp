#include "Game/AI/Action/actionPlayerDiveMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerDiveMove::PlayerDiveMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDiveMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDiveMove::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.reset(0x8);
        controller->mFlags.reset(0x20000);
    }
}

void PlayerDiveMove::loadParams_() {
    getStaticParam(&mAnmDrivenDist_s, "AnmDrivenDist");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void PlayerDiveMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerDiveMove::isChangeable() const {
    return false;
}

}  // namespace uking::action
