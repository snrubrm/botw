#include "Game/AI/AI/aiSiteBossShootNormalArrowRoot.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

SiteBossShootNormalArrowRoot::SiteBossShootNormalArrowRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossShootNormalArrowRoot::~SiteBossShootNormalArrowRoot() = default;

bool SiteBossShootNormalArrowRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossShootNormalArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossShootNormalArrowRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossShootNormalArrowRoot::loadParams_() {
    getStaticParam(&mArrowNum_s, "ArrowNum");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mAvoidCountMax_s, "AvoidCountMax");
    getStaticParam(&mSeqAvoidRate_s, "SeqAvoidRate");
    getStaticParam(&mUpDownAvoidRate_s, "UpDownAvoidRate");
    getStaticParam(&mHoldTime_s, "HoldTime");
    getStaticParam(&mInitHoldTime_s, "InitHoldTime");
    getStaticParam(&mAvoidLifeRate_s, "AvoidLifeRate");
    getStaticParam(&mAvoidAngle_s, "AvoidAngle");
    getStaticParam(&mAvoidDist_s, "AvoidDist");
    getStaticParam(&mAvoidDistRand_s, "AvoidDistRand");
    getStaticParam(&mAvoidWaitCount_s, "AvoidWaitCount");
    getStaticParam(&mAvoidWaitCountRand_s, "AvoidWaitCountRand");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mTrigEventAtHold_s, "TrigEventAtHold");
    getStaticParam(&mSpineControlOffsetAngleLR_s, "SpineControlOffsetAngleLR");
    getStaticParam(&mSpineControlOffsetAngleUD_s, "SpineControlOffsetAngleUD");
    getStaticParam(&mIsFinishAtNoDevice_s, "IsFinishAtNoDevice");
    getStaticParam(&mIsIgnoreCancelAttack_s, "IsIgnoreCancelAttack");
    getStaticParam(&mIsKeepDistance_s, "IsKeepDistance");
    getStaticParam(&mArrowName_s, "ArrowName");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getDynamicParam(&mIsCancelAttack_d, "IsCancelAttack");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SiteBossShootNormalArrowRoot::m34() {
    return _120 <= sead::Mathf::epsilon();
}

void SiteBossShootNormalArrowRoot::m35() {
    changeChild("子機発射");
}

void SiteBossShootNormalArrowRoot::m39() {}

void SiteBossShootNormalArrowRoot::m40() {}

void SiteBossShootNormalArrowRoot::m41() {}

void SiteBossShootNormalArrowRoot::m42() {}

s32 SiteBossShootNormalArrowRoot::m43() {
    return 1;
}

s32 SiteBossShootNormalArrowRoot::m44() {
    return 2;
}

void SiteBossShootNormalArrowRoot::m45(sead::Vector3f* out) {
    *out = *mTargetPos_d;
}

void SiteBossShootNormalArrowRoot::m46(sead::Vector3f* out) {
    m45(out);
}

bool SiteBossShootNormalArrowRoot::m48() {
    return _144 >= u32(*mArrowNum_s);
}

bool SiteBossShootNormalArrowRoot::sub_7100588164(bool a1) {
    return _120 <= sead::Mathf::epsilon();
}

}  // namespace uking::ai
