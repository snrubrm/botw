#include "Game/AI/Action/actionPlayerGrabWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGrabWait::PlayerGrabWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
}

void PlayerGrabWait::leave_() {}

void PlayerGrabWait::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGrabWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
