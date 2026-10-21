#include "Game/Actor/Player/Action/actionPlayerJump.h"
#include <algorithm>
#include <cstring>
#include "Game/Actor/aiUnk_7101e7c5d0.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerJump::PlayerJump(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mJumpHeight_s, 0, 0x50);
}

void PlayerJump::sub_71007F7FBC() {
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

// NON_MATCHING: the established u32 turn angle is copied into an angle object for x_53.
void PlayerJump::enter_(ksys::act::ai::InlineParamPack* params) {
    static_cast<ksys::act::Player*>(mActor)->_17f1 =
        static_cast<ksys::act::Player*>(mActor)->_cf0.isOnBit(17);
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x100000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x200000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17f1) {
        player->_cf8.set(0x8);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    player->_c44.set(0x40000);
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100892098())
        static_cast<ksys::act::Player*>(mActor)->_c44.set(0x1000000);
    if (mActor->getASList()->x_1(0, 0) != "Slide" &&
        mActor->getASList()->x_1(0, 0) != "SlideBrake") {
        player = static_cast<ksys::act::Player*>(mActor);
        if (player->_209c > 0.05f) {
            player->x_53(ksys::act::Player::Unk1(player->_1c74));
            static_cast<ksys::act::Player*>(mActor)->_1c68.value =
                static_cast<ksys::act::Player*>(mActor)->_1c74;
        } else {
            const auto angle = player->x_5();
            static_cast<ksys::act::Player*>(mActor)->_1c68 = angle;
        }
    }
    sub_71007F7FBC();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Jump", true, -1.0f);
    sub_71007F80BC();
    static_cast<ksys::act::Player*>(mActor)->x_16();
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f2 = true;
    static_cast<ksys::act::Player*>(mActor)->_17f3 =
        static_cast<ksys::act::Player*>(mActor)->_1fa8 > 1.25f;
    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1cb0 == 0x44) {
        player->_c44.set(0x80000);
        player = static_cast<ksys::act::Player*>(mActor);
    }
    player->_1ec0 = ksys::Timer(4.0f, 4.0f, -1.0f);
}

void PlayerJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x80000);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x1000000);
}

void PlayerJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpHeightAddByAngle_s, "JumpHeightAddByAngle");
    getStaticParam(&mJumpHeightAddBySpeed_s, "JumpHeightAddBySpeed");
    getStaticParam(&mJumpHeightMaxDecRateByWater_s, "JumpHeightMaxDecRateByWater");
    getStaticParam(&mIgnoreWaterHeight_s, "IgnoreWaterHeight");
    getStaticParam(&mEnergyJump_s, "EnergyJump");
    getStaticParam(&mEnergyDashJump_s, "EnergyDashJump");
    getStaticParam(&mEnergyUseDiam1_s, "EnergyUseDiam1");
    getStaticParam(&mEnergyUseDiam2_s, "EnergyUseDiam2");
    getStaticParam(&mEnergyUseDiam3_s, "EnergyUseDiam3");
}

// NON_MATCHING: (1) the original reads the arguments of sub_710086843C (0.5f, 0x20000000, 0x200000) from unnamed rodata
// globals (see PlayerWallJump); (2) the AS speed ternary loads the ASList / member pointer in both arms (as BowFall).
void PlayerJump::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 speed = player->_c40.isOnBit(13) ? player->m301() : 1.0f;
    player->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, speed);
    player->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, speed);
    if (!static_cast<ksys::act::Player*>(mActor)->_17d0->playerCheckController(2))
        static_cast<ksys::act::Player*>(mActor)->_17f2 = false;
    static_cast<ksys::act::Player*>(mActor)->sub_7100881418();
    static_cast<ksys::act::Player*>(mActor)->sub_71008931C4();
    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c44.isOnBit(8) && !player->_d11) {
        player->x_37();
        player = static_cast<ksys::act::Player*>(mActor);
    }
    if (player->m179()) {
        static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
        if (ksys::act::playerIsReloadingOrChargingOrShootingBow(static_cast<ksys::act::Player*>(mActor)))
            static_cast<ksys::act::Player*>(mActor)->x_37();
    }
    sub_71007F7FBC();
    if (!static_cast<ksys::act::Player*>(mActor)->_17f0) {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    } else if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(0x13)) {
        static_cast<ksys::act::Player*>(mActor)->_c40.set(0x400000);
    }
    player = static_cast<ksys::act::Player*>(mActor);
    if ((player->m359() || !player->m179() || player->_c40.isOnBit(30)) &&
        (!static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(8) ||
         static_cast<ksys::act::Player*>(mActor)->_d11) &&
        static_cast<ksys::act::Player*>(mActor)->_17f1) {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        p->sub_710086843C(0.5f, &p->_1c68, 0x20000000, 0x200000);
    }
    static_cast<ksys::act::Player*>(mActor)->_185c.update();
    if (static_cast<ksys::act::Player*>(mActor)->_17f3)
        static_cast<ksys::act::Player*>(mActor)->x_34(*mEnergyDashJump_s, false);
    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_d11 && player->getConnectedCalcChild()) {
        if (auto* controller = mActor->getCharacterController()) {
            if (controller->sub_7100F62B80().y < 0.0f &&
                static_cast<ksys::act::Player*>(mActor)->_1770.y >
                    static_cast<ksys::act::Player*>(mActor)->_178c) {
                static_cast<ksys::act::Player*>(mActor)->m228(false);
            }
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

// 0x71007f80bc (placeholder name): turns the anim-driven jump angle and the water depth into the jump
// height and charges the stamina for the jump.
// NON_MATCHING: util::sub_71011EE4B8 takes its 4-byte angle by value (indirectly); the original passes the
// address of _1c90 straight in, ours copies it to a stack temporary, and the original copies _1c68 for
// sub_710087CEEC where ours passes its address. The reads of _20d4 are scheduled a little differently too.
void PlayerJump::sub_71007F80BC() {
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20000);

    f32 height = *mJumpHeight_s;
    f32 angle = static_cast<f32>(ksys::util::sub_71011EE4B8(
                    static_cast<ksys::act::Player*>(mActor)->sub_710087CEEC(
                        static_cast<ksys::act::Player*>(mActor)->_1c68))) *
                ksys::util::sUnk_7101EC6BA4;
    if (angle > 180.0f)
        angle -= 360.0f;

    const f32 factor = std::min(static_cast<ksys::act::Player*>(mActor)->_20bc.value, 0.3f);
    height += factor * (angle * *mJumpHeightAddByAngle_s) / (uking::sUnk_7101e7c2e0 * 1.5f);
    height += factor * *mJumpHeightAddBySpeed_s;
    height = std::max(height, 0.0f);

    if (static_cast<ksys::act::Player*>(mActor)->_20d4 >
        static_cast<ksys::act::Player*>(mActor)->_1770.y) {
        const f32 depth = (static_cast<ksys::act::Player*>(mActor)->_20d4 -
                           static_cast<ksys::act::Player*>(mActor)->_1770.y) -
                          *mIgnoreWaterHeight_s;
        if (depth > 0.0f) {
            height *= 1.0f - *mJumpHeightMaxDecRateByWater_s *
                                (depth / (uking::sUnk_7101e7c5c8 - *mIgnoreWaterHeight_s));
            if (height < 0.0f)
                height = 0.0f;
        }
    }

    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(height *
                                   static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed());
    }

    static_cast<ksys::act::Player*>(mActor)->_185c = ksys::Timer(21.0f, 21.0f);

    f32 energy = *mEnergyJump_s;
    const f32 energy_angle =
        static_cast<f32>(ksys::util::sub_71011EE4B8(
            static_cast<ksys::act::Player*>(mActor)->_1c90)) *
        ksys::util::sUnk_7101EC6BA4;
    if (energy_angle >= 45.0f)
        energy *= *mEnergyUseDiam3_s;
    else if (energy_angle >= 30.0f)
        energy *= *mEnergyUseDiam2_s;
    else if (energy_angle >= 15.0f)
        energy *= *mEnergyUseDiam1_s;
    static_cast<ksys::act::Player*>(mActor)->decreaseStaminaForActionMaybe(energy);
}

bool PlayerJump::isChangeable() const {
    return true;
}

bool PlayerJump::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return true;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    return player->_1770.y < player->_2158 - 0.5f;
}

}  // namespace uking::action
