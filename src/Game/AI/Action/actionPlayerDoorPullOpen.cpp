#include "Game/AI/Action/actionPlayerDoorPullOpen.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerDoorPullOpen::PlayerDoorPullOpen(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDoorPullOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DoorPullOpen", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
}

void PlayerDoorPullOpen::leave_() {}

void PlayerDoorPullOpen::calc_() {
    PlayerAction::calc_();
}

bool PlayerDoorPullOpen::isChangeable() const {
    return false;
}

}  // namespace uking::action
