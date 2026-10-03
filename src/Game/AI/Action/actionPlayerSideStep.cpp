#include "Game/AI/Action/actionPlayerSideStep.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/System/Timer.h"
#include <cstring>

namespace uking::action {

PlayerSideStep::PlayerSideStep(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mSpeedF_s, 0, 0x48);
}

void PlayerSideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSideStep::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x10000);
    static_cast<ksys::act::Player*>(mActor)->_c4c.reset(0x100);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x1000000);
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0.0f, 0.0f);
    if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr()))
        manager->_210 &= 0xfd6c;
}

void PlayerSideStep::loadParams_() {
    getStaticParam(&mSpeedF_s, "SpeedF");
    getStaticParam(&mHeight_s, "Height");
    getStaticParam(&mFSpeedF_s, "FSpeedF");
    getStaticParam(&mFHeight_s, "FHeight");
    getStaticParam(&mUHeight_s, "UHeight");
    getStaticParam(&mNoDamageTime_s, "NoDamageTime");
    getStaticParam(&mJustAvoidTime_s, "JustAvoidTime");
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
    getStaticParam(&mMySlowStartFrame_s, "MySlowStartFrame");
}

void PlayerSideStep::calc_() {
    PlayerAction::calc_();
}

bool PlayerSideStep::isChangeable() const {
    return true;
}

bool PlayerSideStep::isFinished() const {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        return static_cast<ksys::act::Player*>(mActor)->_17f1;
    return false;
}

}  // namespace uking::action
