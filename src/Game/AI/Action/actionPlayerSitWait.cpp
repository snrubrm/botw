#include "Game/AI/Action/actionPlayerSitWait.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSitWait::PlayerSitWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x20000000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EEB8(0.0f);
    static_cast<ksys::act::Player*>(mActor)->_2098 = *mAutoRecoverRate_s;
}

void PlayerSitWait::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EEB8(1.0f);
    static_cast<ksys::act::Player*>(mActor)->_2098 = 1.0f;
}

void PlayerSitWait::loadParams_() {
    getStaticParam(&mAutoRecoverRate_s, "AutoRecoverRate");
    getStaticParam(&mEnergyAutoRecover_s, "EnergyAutoRecover");
}

void PlayerSitWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerSitWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
