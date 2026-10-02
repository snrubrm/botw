#include "Game/AI/Action/actionPlayerSkin.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSkin::PlayerSkin(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSkin::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSkin::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
}

void PlayerSkin::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
}

void PlayerSkin::calc_() {
    PlayerAction::calc_();
}

bool PlayerSkin::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
