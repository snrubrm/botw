#include "Game/AI/AI/aiSiteBossShootNormalArrowRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

namespace {
const sead::Vector3f sUnk_7102421fd0{-1.0f, 0.0f, 0.3f};
}  // namespace

// TU-level variable in .data right after the class vtable (only read in this TU).
static f32 sUnk_7102422198 = 0.05f;

SiteBossShootNormalArrowRoot::SiteBossShootNormalArrowRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossShootNormalArrowRoot::~SiteBossShootNormalArrowRoot() = default;

bool SiteBossShootNormalArrowRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original reads sUnk_7102422198 from memory (ours folds the never-written
// static); the two makeUnit() store sequences are merged differently
void SiteBossShootNormalArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _144 = 0;
    m35();
    _178.setName("Arm_1_R");
    _220.setName("Arm_2_R");
    _220._68 = sead::Matrix34f::ident;
    _178._68 = sead::Matrix34f::ident;
    mActor->boneHandleStuff(&_220, false);
    mActor->boneHandleStuff(&_178, false);
    _150.makeUnit();
    _160.makeUnit();
    _14c = 2;
    _148 = 0;
    _149 = false;
    _174 = false;
    _170 = sUnk_7102422198;
    _12c = ksys::Timer(*mTrigEventAtHold_s, *mTrigEventAtHold_s);
    _138 = ksys::Timer(0, 0);
}

void SiteBossShootNormalArrowRoot::leave_() {
    mActor->sub_71011DA868(&_178);
    mActor->sub_71011DA868(&_220);
    sub_71005D74E8(mActor);
    sub_71005DB51C(mActor, 0.0f, false);
    sub_71005DB558(mActor, 0.0f, false);
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
    return _120.value <= sead::Mathf::epsilon();
}

void SiteBossShootNormalArrowRoot::m35() {
    changeChild("子機発射");
}

// NON_MATCHING: the original reads sUnk_7102422198 from memory (ours folds the never-written static);
// everything else is instruction-identical (an external-linkage global is loaded through the GOT)
void SiteBossShootNormalArrowRoot::m36(bool a1, f32 a2) {
    if (a1)
        m39();
    _170 = sUnk_7102422198;
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target;
    m45(&target);
    pack.addVec3(target, "TargetPos", -1);
    _120 = ksys::Timer(a2, a2);
    _12c = ksys::Timer(*mTrigEventAtHold_s, *mTrigEventAtHold_s);
    changeChild("子機発射", &pack);
}

void SiteBossShootNormalArrowRoot::m39() {}

void SiteBossShootNormalArrowRoot::m40() {}

void SiteBossShootNormalArrowRoot::m41() {}

void SiteBossShootNormalArrowRoot::m42() {}

const sead::Vector3f& SiteBossShootNormalArrowRoot::m51() {
    return sUnk_7102421fd0;
}

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

bool SiteBossShootNormalArrowRoot::m47() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return false;
    return boss->_1560.sub_710066C074() != 0;
}

bool SiteBossShootNormalArrowRoot::m48() {
    return _144 >= u32(*mArrowNum_s);
}

bool SiteBossShootNormalArrowRoot::sub_7100588164(bool a1) {
    return _120.value <= sead::Mathf::epsilon();
}

}  // namespace uking::ai
