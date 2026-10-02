#include "Game/AI/Action/actionPlayerBow.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerBow::PlayerBow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(0, 0);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
}

void PlayerBow::leave_() {}

void PlayerBow::calc_() {
    PlayerAction::calc_();
}

bool PlayerBow::isChangeable() const {
    return true;
}

}  // namespace uking::action
