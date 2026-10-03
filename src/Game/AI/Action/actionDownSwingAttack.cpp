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
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mParams.mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mParams.mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getStaticParam(&mParams.mLoopTime_s, "LoopTime");
    getStaticParam(&mParams.mLoopTimeRand_s, "LoopTimeRand");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mIsSpecialAttack_s, "IsSpecialAttack");
    getStaticParam(&mParams.mSpecialAttackRadius_s, "SpecialAttackRadius");
    getStaticParam(&mParams.mSpineControlOffsetY_s, "SpineControlOffsetY");
}

void DownSwingAttack::calc_() {
    ActionEx::calc_();
}

bool DownSwingAttack::isChangeable() const {
    return false;
}

}  // namespace uking::action
