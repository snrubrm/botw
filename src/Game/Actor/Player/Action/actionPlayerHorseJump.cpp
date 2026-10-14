#include "Game/Actor/Player/Action/actionPlayerHorseJump.h"
#include <cstring>
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerHorseJump::PlayerHorseJump(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mJumpHeight_s, 0, 0x48);
}

void PlayerHorseJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000);
    static_cast<ksys::act::Player*>(mActor)->_c44.set(0x2);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17d0->playerCheckController(13) && !player->m202() && !player->_c44.isOnBit(13) &&
        !player->m178() && player->_d10) {
        static_cast<ksys::act::Player*>(mActor)->_1c68 =
            static_cast<ksys::act::Player*>(mActor)->sub_71008569B8();
    } else {
        static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    }
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("JumpHorseRide", true, -1.0f);
    sub_71007F5E1C();
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(3.0f, 3.0f, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_1ec0 = ksys::Timer(4.0f, 4.0f, -1.0f);
}

// NON_MATCHING: the original selects the speed pointer by loading the static param pointer (and mActor) in every
// gear branch and merges the stores in two tails; ours selects the address of the param and loads once.
void PlayerHorseJump::sub_71007F5E1C() {
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20000);
    static_cast<ksys::act::Player*>(mActor)->_cfc.reset(0x1);
    const f32 height = *mJumpHeight_s * static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17d0->playerCheckController(13) && !player->m202() && !player->_c44.isOnBit(13) &&
        !player->m178() && player->_d10) {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        const sead::Vector3f target = p->getVelocity() * 2 + p->_1770;
        p->sub_7100894384(height, target, *mJumpMaxSpeedF_s, *mAimDistOffset_s);
    } else {
        const int gear = *mJumpGear_d;
        const f32* speed = nullptr;
        if (*mIsLargeHorse_d) {
            switch (gear) {
            case 2:
                speed = mJumpSpeedF3_s;
                break;
            case 1:
                speed = mJumpSpeedF2_s;
                break;
            case 0:
                speed = mJumpSpeedF_s;
                break;
            default:
                if (gear >= 3)
                    speed = mJumpSpeedF4_s;
                break;
            }
        } else if (gear <= 1) {
            speed = mJumpSpeedF_s;
        } else if (gear == 2) {
            speed = mJumpSpeedF2_s;
        } else {
            speed = mJumpSpeedF4_s;
        }
        if (speed) {
            auto* p = static_cast<ksys::act::Player*>(mActor);
            p->_20bc.value = *speed;
            p->_20bc.prev_value = *speed;
        }
    }
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(height);
    }
}

void PlayerHorseJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x2);
}

void PlayerHorseJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpSpeedF2_s, "JumpSpeedF2");
    getStaticParam(&mJumpSpeedF3_s, "JumpSpeedF3");
    getStaticParam(&mJumpSpeedF4_s, "JumpSpeedF4");
    getStaticParam(&mJumpMaxSpeedF_s, "JumpMaxSpeedF");
    getStaticParam(&mAimDistOffset_s, "AimDistOffset");
    getDynamicParam(&mJumpGear_d, "JumpGear");
    getDynamicParam(&mIsLargeHorse_d, "IsLargeHorse");
}

// NON_MATCHING: the original reads the arguments of sub_710086843C (0.5f, 0x20000000, 0x200000) from rodata
// constants with external linkage (see PlayerWallJump); the AS speed ternary loads the ASList / member pointer in
// both arms (as PlayerJump).
void PlayerHorseJump::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 speed = player->_c40.isOnBit(13) ? player->m301() : 1.0f;
    player->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, speed);
    player->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, speed);
    static_cast<ksys::act::Player*>(mActor)->sub_7100881418();

    auto* as_list = mActor->getASList();
    player = static_cast<ksys::act::Player*>(mActor);
    as_list->sub_710115EFD0(0, true, false, player->get17d0()->getLeftStick().length());
    auto* current = static_cast<ksys::act::Player*>(mActor);
    current->getASList()->x_6(
        6, 0,
        ksys::util::sub_71011EE4B8(ksys::util::angleDiff(current->_1c74, current->x_5())) *
            ksys::util::sUnk_7101EC6BA4);
    auto* p = static_cast<ksys::act::Player*>(mActor);
    p->sub_710086843C(0.5f, &p->_1c68, 0x20000000, 0x200000);

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

    if (static_cast<ksys::act::Player*>(mActor)->_1770.y <
        static_cast<ksys::act::Player*>(mActor)->_2158 - 0.5f)
        setFinished();

    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1844.value <= sead::Mathf::epsilon()) {
        if (player->getVelocity().y < 0.0f)
            player->_c44.reset(0x2);
    } else {
        player->_1844.update();
    }

    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerHorseJump::isChangeable() const {
    return true;
}

bool PlayerHorseJump::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return true;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    return player->_1770.y < player->_2158 - 0.5f;
}

}  // namespace uking::action
