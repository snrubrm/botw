#include "Game/AI/Action/actionPlayerLadderJumpLand.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLadderJumpLand::PlayerLadderJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderJumpLand::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1810;
    if (auto* controller = mActor->getCharacterController()) {
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    }
}

void PlayerLadderJumpLand::loadParams_() {
    getDynamicParam(&mMoveDir_d, "MoveDir");
}

void PlayerLadderJumpLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderJumpLand::isChangeable() const {
    return true;
}

}  // namespace uking::action
