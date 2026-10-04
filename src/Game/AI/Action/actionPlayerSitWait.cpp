#include "Game/AI/Action/actionPlayerSitWait.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSitWait::PlayerSitWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x20000000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
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
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    static_cast<ksys::act::Player*>(mActor)->_1cb0 = 0;
    static_cast<ksys::act::Player*>(mActor)->sub_710084AD5C(*mEnergyAutoRecover_s, false);
    if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(14)) {
        ui::sub_7100A95F5C(static_cast<ksys::act::Player*>(mActor)->_1cb0);
        setFinished();
    }
}

bool PlayerSitWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
