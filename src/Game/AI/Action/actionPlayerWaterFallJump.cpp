#include "Game/AI/Action/actionPlayerWaterFallJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerWaterFallJump::PlayerWaterFallJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWaterFallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x8000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWaterfallJump", true,
                                                                       -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        if (!ksys::gdt::getFlag_Water_Relic_PlayerInBattleArea())
            controller->sub_7100F62B70(*mJumpHeight_s);
        else if (static_cast<ksys::act::Player*>(mActor)->_c48.isOnBit(24))
            controller->sub_7100F62B70(*mJumpHeightWithZora_s);
        else
            controller->sub_7100F62B70(*mJumpHeightWaterRemain_s);
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32& speed = *mJumpSpeedF_s;
    player->_20bc = speed;
    player->_20c0 = speed;
}

void PlayerWaterFallJump::leave_() {
    PlayerAction::leave_();
}

void PlayerWaterFallJump::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpHeightWaterRemain_s, "JumpHeightWaterRemain");
    getStaticParam(&mJumpHeightWithZora_s, "JumpHeightWithZora");
}

void PlayerWaterFallJump::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (mActor->getVelocity().y <= 0.01f)
        setFinished();
}

bool PlayerWaterFallJump::isChangeable() const {
    return false;
}

}  // namespace uking::action
