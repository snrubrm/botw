#include "Game/AI/Action/actionPlayerJump.h"
#include <cstring>
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
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

void PlayerJump::calc_() {
    PlayerAction::calc_();
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
