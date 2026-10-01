#include "Game/AI/Action/actionDownSwingAttack.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
DownSwingAttack::DownSwingAttack(const InitArg& arg) : ActionEx(arg) {}

DownSwingAttack::~DownSwingAttack() = default;

void DownSwingAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void DownSwingAttack::leave_() {
    ActionEx::leave_();
}

void DownSwingAttack::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getStaticParam(&mLoopTime_s, "LoopTime");
    getStaticParam(&mLoopTimeRand_s, "LoopTimeRand");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsSpecialAttack_s, "IsSpecialAttack");
    getStaticParam(&mSpecialAttackRadius_s, "SpecialAttackRadius");
    getStaticParam(&mSpineControlOffsetY_s, "SpineControlOffsetY");
}

void DownSwingAttack::calc_() {
    ActionEx::calc_();
}

bool DownSwingAttack::isChangeable() const {
    return false;
}

}  // namespace uking::action
