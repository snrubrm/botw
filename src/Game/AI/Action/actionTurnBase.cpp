#include "Game/AI/Action/actionTurnBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "math/seadMathCalcCommon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TurnBase::TurnBase(const InitArg& arg) : ActionEx(arg) {}

TurnBase::~TurnBase() = default;

void TurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
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
    ActionEx::calc_();
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
