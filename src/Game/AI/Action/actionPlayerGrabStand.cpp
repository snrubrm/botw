#include "Game/AI/Action/actionPlayerGrabStand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGrabStand::PlayerGrabStand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabStand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GrabStand", true, -1.0f);
}

void PlayerGrabStand::leave_() {}

void PlayerGrabStand::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    m32();
}

bool PlayerGrabStand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
