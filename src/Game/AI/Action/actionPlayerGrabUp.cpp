#include "Game/AI/Action/actionPlayerGrabUp.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGrabUp::PlayerGrabUp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabUp::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c4c.reset(0x4000);
}

void PlayerGrabUp::calc_() {
    PlayerAction::calc_();
}

bool PlayerGrabUp::isChangeable() const {
    return false;
}

}  // namespace uking::action
