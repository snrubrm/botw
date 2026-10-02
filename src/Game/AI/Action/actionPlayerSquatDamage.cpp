#include "Game/AI/Action/actionPlayerSquatDamage.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSquatDamage::PlayerSquatDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSquatDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSquatDamage::leave_() {
    PlayerAction::leave_();
}

void PlayerSquatDamage::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerSquatDamage::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
