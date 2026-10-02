#include "Game/AI/Action/actionPlayerIceBreak.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerIceBreak::PlayerIceBreak(const InitArg& arg) : PlayerAction(arg) {}

void PlayerIceBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerIceBreak::leave_() {
    PlayerAction::leave_();
}

void PlayerIceBreak::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    m32();
}

bool PlayerIceBreak::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
