#include "Game/AI/Action/actionPlayerSitEnd.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerSitEnd::PlayerSitEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSitEnd::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(1.0f);
}

void PlayerSitEnd::calc_() {
    PlayerAction::calc_();
}

bool PlayerSitEnd::isChangeable() const {
    return false;
}

}  // namespace uking::action
