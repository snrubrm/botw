#include "Game/AI/Action/actionPlayerDiveMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerDiveMove::PlayerDiveMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDiveMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x2000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.set(0x8);
        controller->mFlags.set(0x20000);
    }
    _38 = 0;
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
