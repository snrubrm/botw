#include "Game/AI/Action/actionSiteBossSpearAttackBase.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::action {

SiteBossSpearAttackBase::SiteBossSpearAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSpearAttackBase::~SiteBossSpearAttackBase() = default;

bool SiteBossSpearAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSpearAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSpearAttackBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSpearAttackBase::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mTargetOffsetLowAtRotate_s, "TargetOffsetLowAtRotate");
    getStaticParam(&mTargetOffsetHighAtRotate_s, "TargetOffsetHighAtRotate");
    getStaticParam(&mCanBreakIceBlock_s, "CanBreakIceBlock");
    getStaticParam(&mIsOnSpine1Rotate_s, "IsOnSpine1Rotate");
    getStaticParam(&mIsOnSpine2Rotate_s, "IsOnSpine2Rotate");
    getStaticParam(&mIsOnSpine3Rotate_s, "IsOnSpine3Rotate");
    getStaticParam(&mCanJustAvoid_s, "CanJustAvoid");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossSpearAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SiteBossSpearAttackBase::isFinished() const {
    return isFinishedAS(0, 0);
}

int SiteBossSpearAttackBase::m34() {
    return *mAtMinDamage_s;
}

int SiteBossSpearAttackBase::m32() {
    return 322;
}

int SiteBossSpearAttackBase::m33() {
    int level = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534 & ~3;
        if (kind == 4)
            level = 3;
        else if (kind == 8)
            level = 4;
    }
    return *mAttackPower_s + *mAddAttackPower_s * level;
}

}  // namespace uking::action
