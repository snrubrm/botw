#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MoveBase::MoveBase(const InitArg& arg) : ActionEx(arg) {}

MoveBase::~MoveBase() = default;

void MoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void MoveBase::leave_() {
    ActionEx::leave_();
}

void MoveBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWallHitLimitTime_s, "WallHitLimitTime");
    getStaticParam(&mMoveAngCliffLimitTime_s, "MoveAngCliffLimitTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
    getStaticParam(&mFollowGround_s, "FollowGround");
    getStaticParam(&mIgnoreLastCurve_s, "IgnoreLastCurve");
    getStaticParam(&mIgnoreDecelerationFrontCliff_s, "IgnoreDecelerationFrontCliff");
    getStaticParam(&mIgnoreMoveDirCoHit_s, "IgnoreMoveDirCoHit");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MoveBase::calc_() {
    ActionEx::calc_();
}

void MoveBase::m33() {
    setFinished();
}

f32 MoveBase::m34() {
    return 2.0f;
}

void MoveBase::m32(sead::Vector3f* dir) {
    mActor->getMtx().getBase(*dir, 2);
    dir->normalize();
    dir->y = 0;
    dir->normalize();
}

}  // namespace uking::action
