#include "Game/AI/Action/actionPlayerWallDashUp.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

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
    PlayerAction::calc_();
}

bool PlayerWallDashUp::isChangeable() const {
    return true;
}

}  // namespace uking::action
