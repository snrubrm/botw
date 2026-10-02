#include "Game/AI/Action/actionPlayerLadderJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLadderJump::PlayerLadderJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderJump::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1810;
}

void PlayerLadderJump::loadParams_() {
    getStaticParam(&mEnergyJump_s, "EnergyJump");
}

void PlayerLadderJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderJump::isChangeable() const {
    return true;
}

}  // namespace uking::action
