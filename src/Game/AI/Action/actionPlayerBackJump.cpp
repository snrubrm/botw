#include "Game/AI/Action/actionPlayerBackJump.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerBackJump::PlayerBackJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBackJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBackJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x10000);
    static_cast<ksys::act::Player*>(mActor)->_c4c.reset(0x100);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x1000000);
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
    if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr()))
        manager->_210 &= ~0x24c;
    static_cast<ksys::act::Player*>(mActor)->sub_710086952C();
}

void PlayerBackJump::loadParams_() {
    getStaticParam(&mBJSpeedF_s, "BJSpeedF");
    getStaticParam(&mBJHeight_s, "BJHeight");
    getStaticParam(&mNoDamageTime_s, "NoDamageTime");
    getStaticParam(&mJustAvoidTime_s, "JustAvoidTime");
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
    getStaticParam(&mMySlowStartFrame_s, "MySlowStartFrame");
    getDynamicParam(&mEnableSwordInput_d, "EnableSwordInput");
}

void PlayerBackJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerBackJump::isChangeable() const {
    return true;
}

bool PlayerBackJump::isFinished() const {
    if (!static_cast<const ksys::act::Player*>(mActor)->isSurfingOnGround())
        return false;
    return sub_71007D8358();
}

bool PlayerBackJump::sub_71007D8358() const {
    if (mActor->getASList()->x_4(0, 0))
        return true;
    if (mActor->getASList()->x(2, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return true;
    return mActor->getASList()->x_1(0, 0) != "BackJump";
}

}  // namespace uking::action
