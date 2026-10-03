#include "Game/AI/Action/actionPlayerHorseJump.h"
#include <cstring>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerHorseJump::PlayerHorseJump(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mJumpHeight_s, 0, 0x48);
}

void PlayerHorseJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
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

void PlayerHorseJump::calc_() {
    PlayerAction::calc_();
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
