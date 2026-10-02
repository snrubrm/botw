#include "Game/AI/Action/actionPlayerSwimDamage.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimDamage::PlayerSwimDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimDamage::leave_() {}

void PlayerSwimDamage::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerSwimDamage::isChangeable() const {
    return false;
}

}  // namespace uking::action
