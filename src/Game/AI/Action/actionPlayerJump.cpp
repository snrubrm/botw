#include "Game/AI/Action/actionPlayerJump.h"
#include <cstring>
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

void PlayerJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
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
