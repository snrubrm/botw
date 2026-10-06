#include "Game/AI/Action/actionPlayerWallJump.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerWallJump::PlayerWallJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWallJump::sub_7100823C4C() {
    auto* as_list = mActor->getASList();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    as_list->sub_710115EFD0(0, true, false, player->get17d0()->getLeftStick().length());
    if (static_cast<ksys::act::Player*>(mActor)->get17d0()->sub_71008BD364() == 0.0f) {
        static_cast<ksys::act::Player*>(mActor)->getASList()->x_6(6, 0, 0.0f);
    } else {
        auto* current = static_cast<ksys::act::Player*>(mActor);
        current->getASList()->x_6(6, 0,
                                  ksys::util::sub_71011EE4B8(ksys::util::angleDiff(
                                      current->_1c74, current->x_5())) *
                                      ksys::util::sUnk_7101EC6BA4);
    }
}

// NON_MATCHING: the original loads `mJumpSpeedF_s` once for both _20bc stores; here the pointer is reloaded.
void PlayerWallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x100000);
    sub_7100823C4C();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ClimbJumpOff", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20000);
    static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mJumpHeight_s);
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32* speed = mJumpSpeedF_s;
    player->_20bc.value = *speed;
    player->_20bc.prev_value = *speed;
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
}

void PlayerWallJump::leave_() {}

void PlayerWallJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
}

// NON_MATCHING: the original reads the arguments of sub_710086843C (0.5f, 0x20000000, 0x200000) from rodata
// constants with external linkage (loaded through the GOT).
void PlayerWallJump::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_71008931C4();
    if (static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(8) &&
        !static_cast<ksys::act::Player*>(mActor)->_d11)
        static_cast<ksys::act::Player*>(mActor)->x_37();
    if (static_cast<ksys::act::Player*>(mActor)->m179()) {
        static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
        if (ksys::act::playerIsReloadingOrChargingOrShootingBow(
                static_cast<ksys::act::Player*>(mActor)))
            static_cast<ksys::act::Player*>(mActor)->x_37();
    }
    sub_7100823C4C();
    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        if (static_cast<ksys::act::Player*>(mActor)->get17d0()->controllerCheckPressedMaybe(19))
            static_cast<ksys::act::Player*>(mActor)->_c40.set(0x400000);
    } else {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    }
    static_cast<ksys::act::Player*>(mActor)->sub_710086843C(
        0.5f, &static_cast<ksys::act::Player*>(mActor)->_1c68, 0x20000000, 0x200000);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerWallJump::isChangeable() const {
    return true;
}

bool PlayerWallJump::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return true;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    return player->_1770.y < player->_2158 - 0.5f;
}

}  // namespace uking::action
