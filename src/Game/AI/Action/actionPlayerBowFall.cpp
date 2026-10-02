#include "Game/AI/Action/actionPlayerBowFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerBowFall::PlayerBowFall(const InitArg& arg) : PlayerFall(arg) {}

void PlayerBowFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerFall::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
}

void PlayerBowFall::leave_() {}

void PlayerBowFall::loadParams_() {
    PlayerFall::loadParams_();
}

void PlayerBowFall::calc_() {
    PlayerFall::calc_();
}

bool PlayerBowFall::isChangeable() const {
    return true;
}

}  // namespace uking::action
