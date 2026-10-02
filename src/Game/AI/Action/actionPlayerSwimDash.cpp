#include "Game/AI/Action/actionPlayerSwimDash.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimDash::PlayerSwimDash(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimDash::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

// NON_MATCHING: the original copies the velocity once more (element-wise self-copy of x/z after the call)
void PlayerSwimDash::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f vel;
        controller->sub_7100F5F598(&vel);
        if (vel.y > 0.0f) {
            vel.y = 0.0f;
            controller->sub_7100F5F6FC(vel);
        }
    }
}

void PlayerSwimDash::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
}

void PlayerSwimDash::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimDash::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
