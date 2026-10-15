#include "Game/Actor/Action/actionMoveBase.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

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

// NON_MATCHING: normalized up-vector stores and fallback loads are reordered.
void MoveBase::m35(ksys::phys::CharacterController* controller, const sead::Vector3f& dir) {
    sub_7100741038(&_a8, mActor);
    const f32 base_rot_ratio = *mBaseRotRatio_s;
    const f32 rot_speed = *mRotSpd_s;
    ksys::VFR::lerp(&_d8, rot_speed, base_rot_ratio);
    sead::Vector3f up;
    if (!*mFollowGround_s || !controller->sub_7100F5F234(&up)) {
        const auto gravity = controller->get70();
        const f32 length = gravity.length();
        up = -gravity;
        if (length > 0.0f)
            up *= 1.0f / length;
        if (length < sead::Mathf::epsilon())
            up = sead::Vector3f::ey;
    }
    sead::Matrix34f target;
    ksys::util::sub_71011F00EC(&target, dir, up, sead::Vector3f::zero, true);
    sub_710074149C(&_a8, target, base_rot_ratio, _d8, _d8 * 0.25f);
    const f32 angular_speed = mActor->getAngVelocity().length();
    if (_d8 > angular_speed)
        _d8 = angular_speed;
    sub_71007419F4(_a8, controller);
}

}  // namespace uking::action
