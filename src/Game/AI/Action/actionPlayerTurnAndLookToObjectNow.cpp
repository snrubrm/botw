#include "Game/AI/Action/actionPlayerTurnAndLookToObjectNow.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerTurnAndLookToObjectNow::PlayerTurnAndLookToObjectNow(const InitArg& arg)
    : PlayerLookAtObjectNow(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
PlayerTurnAndLookToObjectNow::~PlayerTurnAndLookToObjectNow() {
    ;
}

bool PlayerTurnAndLookToObjectNow::init_(sead::Heap* heap) {
    return PlayerLookAtObjectNow::init_(heap);
}

void PlayerTurnAndLookToObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerLookAtObjectNow::enter_(params);
}

void PlayerTurnAndLookToObjectNow::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    static_cast<ksys::act::Player*>(mActor)->_2d64 = true;
}

void PlayerTurnAndLookToObjectNow::loadParams_() {
    PlayerLookAtObjectNow::loadParams_();
}

void PlayerTurnAndLookToObjectNow::calc_() {
    PlayerLookAtObjectNow::calc_();
}

}  // namespace uking::action
