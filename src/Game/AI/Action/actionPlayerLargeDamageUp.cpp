#include "Game/AI/Action/actionPlayerLargeDamageUp.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLargeDamageUp::PlayerLargeDamageUp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLargeDamageUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLargeDamageUp::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
    static_cast<ksys::act::Player*>(mActor)->_c50.resetBit(30);
}

void PlayerLargeDamageUp::calc_() {
    PlayerAction::calc_();
}

bool PlayerLargeDamageUp::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
