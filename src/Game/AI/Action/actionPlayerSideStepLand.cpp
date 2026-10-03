#include "Game/AI/Action/actionPlayerSideStepLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSideStepLand::PlayerSideStepLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSideStepLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x1000000);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c40.isOnBit(8)) {
        player->_cf0.set(0x2000000);
        static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x10000000);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->_c98.isOnBit(17)) {
        player->_c4c.set(0x4);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->_c44.isOnBit(8) && !player->_d11)
        player->switchToAnimSequenceMaybe("StepLandLower", true, -1.0f);
    else
        player->switchToAnimSequenceMaybe("StepLand", true, -1.0f);

    player = static_cast<ksys::act::Player*>(mActor);
    player->_17f1 = player->_d1c > 1;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_c50.set(0x1);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_211c = 0;

    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c40.isOnBit(9))
        player->_1d70 = ksys::Timer(9999.0f, 9999.0f);
}

void PlayerSideStepLand::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
}

void PlayerSideStepLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerSideStepLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
