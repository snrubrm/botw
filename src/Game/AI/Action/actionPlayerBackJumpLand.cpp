#include "Game/AI/Action/actionPlayerBackJumpLand.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
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

// NON_MATCHING: identical instructions, but ours keeps `&mActor` (this + 8) in an extra callee-saved register (x20) from
// the first load on (pre-indexed `ldr x0, [x20, #8]!`); the original reloads `[x19, #8]` everywhere.
void PlayerBackJumpLand::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(9)) {
        static_cast<ksys::act::Player*>(mActor)->_1cb0 = 78;
        ksys::act::Attention::instance()->sub_7100D744B8(
            static_cast<ksys::act::Player*>(mActor)->get1280());
    }
    static_cast<ksys::act::Player*>(mActor)->sub_71008931C4();
    if (static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(8) &&
        !static_cast<ksys::act::Player*>(mActor)->_d11)
        static_cast<ksys::act::Player*>(mActor)->x_37();
    static_cast<ksys::act::Player*>(mActor)->sub_71008893B8(false);
    if (static_cast<ksys::act::Player*>(mActor)->m179()) {
        static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
        if (ksys::act::playerIsReloadingOrChargingOrShootingBow(
                static_cast<ksys::act::Player*>(mActor)))
            static_cast<ksys::act::Player*>(mActor)->x_37();
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(2))
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    if (static_cast<ksys::act::Player*>(mActor)->getASList()->x_4(0, 0)) {
        setFinished();
        return;
    }
    const bool landed = static_cast<ksys::act::Player*>(mActor)->getASList()->x(
        2, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (landed) {
        if (player->_c40.isOnBit(8) || player->_c40.isOnBit(9)) {
            setFailed();
            return;
        }
        _1c = true;
    }
    player->sub_71008B5B8();
}

bool PlayerBackJumpLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
