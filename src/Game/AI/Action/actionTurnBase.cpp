#include "Game/AI/Action/actionTurnBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "math/seadMathCalcCommon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TurnBase::TurnBase(const InitArg& arg) : ActionEx(arg) {}

void TurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;

    sead::Vector3f up;
    m33(&up);
    const f32 speed = mActor->getAngVelocity().length();
    _60.value = speed;
    _60.prev_value = speed;
    sub_7100741034(&_6c, mActor);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);

    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
}

void TurnBase::leave_() {
    ActionEx::leave_();
}

void TurnBase::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRotMinSpeedRatio_s, "RotMinSpeedRatio");
}

void TurnBase::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f up;
    m33(&up);
    sub_7100741038(&_6c, mActor);
    m32(*mPosReduceRatio_s);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    _60.lerp(*mRotSpd_s, 0.16f, *mRotSpd_s);
    _60.updateStats();

    sead::Vector3f normal;
    if (!*mIsFollowGround_s || !controller->sub_7100F5F234(&normal))
        normal = up;

    sead::Vector3f front;
    m34(&front);
    sub_7100741578(&_6c, to_target, normal, true, *mBaseRotRatio_s, _60.value,
                   _60.value * *mRotMinSpeedRatio_s);
    sub_71007419F4(_6c, controller);

    m35(&to_target);
    if (!m36())
        return;
    if (to_target.x == 0.0f && to_target.y == 0.0f && to_target.z == 0.0f) {
        setFinished();
        return;
    }
    if (front.dot(to_target) >= std::cos(*mFinRotate_s))
        setFinished();
}

void TurnBase::m33(sead::Vector3f* up) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        up->set(sead::Vector3f::ey);
        return;
    }
    sead::Vector3f dir = controller->get70();
    dir.negate();
    if (dir.normalize() < sead::Mathf::epsilon())
        dir.set(sead::Vector3f::ey);
    up->set(dir);
}

void TurnBase::m34(sead::Vector3f* front) {
    mActor->getMtx().getBase(*front, 2);
    front->y = 0.0f;
    front->normalize();
}

void TurnBase::m35(sead::Vector3f* dir) {
    dir->y = 0.0f;
    dir->normalize();
}

bool TurnBase::m36() const {
    return true;
}

void TurnBase::m32(f32 x) {
    if (auto* controller = mActor->getCharacterController())
        sub_7100737C0C(controller, x, controller->get70());
}

}  // namespace uking::action
