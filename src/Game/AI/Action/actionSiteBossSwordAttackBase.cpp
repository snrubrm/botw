#include "Game/AI/Action/actionSiteBossSwordAttackBase.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

SiteBossSwordAttackBase::SiteBossSwordAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSwordAttackBase::~SiteBossSwordAttackBase() = default;

bool SiteBossSwordAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSwordAttackBase::leave_() {
    sub_71005D79AC(mActor, 0, act::Unk_71002edaec(1));
}

void SiteBossSwordAttackBase::loadParams_() {
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
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mIsIgnoreCancelAttack_s, "IsIgnoreCancelAttack");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossSwordAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SiteBossSwordAttackBase::isChangeable() const {
    return true;
}

void SiteBossSwordAttackBase::m32() {}

int SiteBossSwordAttackBase::m33() {
    return 66;
}

int SiteBossSwordAttackBase::m35() {
    return *mAtMinDamage_s;
}

bool SiteBossSwordAttackBase::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
