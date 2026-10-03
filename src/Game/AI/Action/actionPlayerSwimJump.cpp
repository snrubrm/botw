#include "Game/AI/Action/actionPlayerSwimJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimJump::PlayerSwimJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x100000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x800000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimJumpSt", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->decreaseStaminaForActionMaybe(*mEnergyJump_s * player->x_67());
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

void PlayerSwimJump::leave_() {}

void PlayerSwimJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mEnergyJump_s, "EnergyJump");
}

void PlayerSwimJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimJump::isChangeable() const {
    return true;
}

}  // namespace uking::action
