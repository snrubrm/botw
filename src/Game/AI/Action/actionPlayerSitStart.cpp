#include "Game/AI/Action/actionPlayerSitStart.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerSitStart::PlayerSitStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSitStart::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(1.0f);
}

void PlayerSitStart::calc_() {
    PlayerAction::calc_();
}

bool PlayerSitStart::isChangeable() const {
    return false;
}

}  // namespace uking::action
