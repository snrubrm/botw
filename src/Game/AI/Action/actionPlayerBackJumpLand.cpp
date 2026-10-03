#include "Game/AI/Action/actionPlayerBackJumpLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerBackJumpLand::PlayerBackJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBackJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
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
    if (player->getASList()->x_1(0, 0) != "BackJumpLand")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("BackJumpLand", true,
                                                                           -1.0f);

    auto* p2 = static_cast<ksys::act::Player*>(mActor);
    p2->_20bc.value = 0;
    p2->_20bc.prev_value = 0;
    p2 = static_cast<ksys::act::Player*>(mActor);
    p2->_c50.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_211c = 0;

    p2 = static_cast<ksys::act::Player*>(mActor);
    if (p2->_c40.isOnBit(9))
        p2->_1d70 = ksys::Timer(9999.0f, 9999.0f);
}

void PlayerBackJumpLand::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
}

void PlayerBackJumpLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerBackJumpLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
