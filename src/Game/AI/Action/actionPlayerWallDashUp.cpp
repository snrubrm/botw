#include "Game/AI/Action/actionPlayerWallDashUp.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerWallDashUp::PlayerWallDashUp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWallDashUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x200000);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 ^ 0x80000000u;
    player->_1834.value = ksys::util::sUnk_7101EC6BA0 & reversed;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1810 = player->_1770;
    player = static_cast<ksys::act::Player*>(mActor);
    player->getASList()->x_6(0x10, 0, player->_1770.y - player->_2158);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("WallDash", true, -1.0f);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1c68 = player->_1834;
    player = static_cast<ksys::act::Player*>(mActor);
    const f32 limit = *mMinSpeedF_s;
    const f32 speed = sead::Mathf::clamp(player->_20bc.value * 0.25f, limit, limit);
    player->_20bc.value = speed;
    player->_20bc.prev_value = speed;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = true;
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
}

void PlayerWallDashUp::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x80000);
}

void PlayerWallDashUp::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mMinSpeedF_s, "MinSpeedF");
    getStaticParam(&mMaxSpeedF_s, "MaxSpeedF");
}

void PlayerWallDashUp::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        if (static_cast<ksys::act::Player*>(mActor)->getASList()->x(
                0x44, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
            if (auto* cc = mActor->getCharacterController()) {
                cc->sub_7100F5EF08(true);
                cc->sub_7100F62B70(*mJumpHeight_s *
                                   static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed());
            }
        }
        static_cast<ksys::act::Player*>(mActor)->actionCommon();
        return;
    }
    static_cast<ksys::act::Player*>(mActor)->sub_710087F29C();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 ^ 0x80000000u;
    player->_1834.value = ksys::util::sUnk_7101EC6BA0 & reversed;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1c68 = player->_1834;
    static_cast<ksys::act::Player*>(mActor)->sub_710086843C(
        0.5f, &static_cast<ksys::act::Player*>(mActor)->_1834, 0x10000000, 0x4000000);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    if (velocity.y / 30.0f < 0.0f || mActor->getASList()->x_4(0, 0)) {
        static_cast<ksys::act::Player*>(mActor)->_c44.set(0x80000);
        setFinished();
    }
}

bool PlayerWallDashUp::isChangeable() const {
    return true;
}

}  // namespace uking::action
