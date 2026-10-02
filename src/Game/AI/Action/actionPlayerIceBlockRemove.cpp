#include "Game/AI/Action/actionPlayerIceBlockRemove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerIceBlockRemove::PlayerIceBlockRemove(const InitArg& arg) : PlayerAction(arg) {}

PlayerIceBlockRemove::~PlayerIceBlockRemove() = default;

void PlayerIceBlockRemove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerIceBlockRemove::leave_() {}

void PlayerIceBlockRemove::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    setFinished();
}

bool PlayerIceBlockRemove::isChangeable() const {
    return false;
}

}  // namespace uking::action
