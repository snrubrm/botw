#include "Game/AI/Action/actionPlayerStopInAir.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerStopInAir::PlayerStopInAir(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStopInAir::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStopInAir::leave_() {
    PlayerAction::leave_();
}

void PlayerStopInAir::loadParams_() {
    getDynamicParam(&mNoFixed_d, "NoFixed");
}

void PlayerStopInAir::calc_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c98.isOnBit(23))
        player->_1810 = sead::Vector3f::zero;
    setFinished();
}

bool PlayerStopInAir::isChangeable() const {
    return true;
}

}  // namespace uking::action
