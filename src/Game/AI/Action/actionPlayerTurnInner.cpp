#include "Game/AI/Action/actionPlayerTurnInner.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerTurnInner::PlayerTurnInner(const InitArg& arg) : PlayerAction(arg) {}

PlayerTurnInner::~PlayerTurnInner() = default;

bool PlayerTurnInner::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerTurnInner::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerTurnInner::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void PlayerTurnInner::loadParams_() {}

void PlayerTurnInner::calc_() {
    PlayerAction::calc_();
}

bool PlayerTurnInner::isChangeable() const {
    return false;
}

}  // namespace uking::action
