#include "Game/Actor/Action/actionMoveBase.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MoveBase::MoveBase(const InitArg& arg) : ActionEx(arg) {}

// NON_MATCHING: target-vector copying and arithmetic register scheduling differ.
void MoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        _98 = sead::Vector2f(mActor->getVelocity().x, mActor->getVelocity().z).length();
        sub_7100741034(&_a8, mActor);
        _d8 = sead::Mathf::clampMax(mActor->getAngVelocity().length(), *mRotSpd_s);
        _cc = *mTargetPos_d;
        _cc -= mActor->getMtx().getTranslation();
        _cc.normalize();
        controller->sub_7100F60AE0();
        sub_7100737708(controller, _98);
        _9c.reset(0.0f, 1.0f);
        mFlags.set(Flag::Changeable);
    }
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
