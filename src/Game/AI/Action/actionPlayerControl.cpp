#include "Game/AI/Action/actionPlayerControl.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerControl::PlayerControl(const InitArg& arg) : PlayerAction(arg) {}

void PlayerControl::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
}

void PlayerControl::leave_() {}

void PlayerControl::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerControl::isChangeable() const {
    return true;
}

}  // namespace uking::action
