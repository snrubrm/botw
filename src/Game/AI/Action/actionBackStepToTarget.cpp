#include "Game/AI/Action/actionBackStepToTarget.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

BackStepToTarget::BackStepToTarget(const InitArg& arg) : ActionEx(arg) {}

void BackStepToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void BackStepToTarget::leave_() {
    ActionEx::leave_();
}

void BackStepToTarget::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mJumpGravity_s, "JumpGravity");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mCheckRotEvent_s, "CheckRotEvent");
}

void BackStepToTarget::calc_() {
    ActionEx::calc_();
}

bool BackStepToTarget::isChangeable() const {
    return false;
}

f32 BackStepToTarget::m42() {
    return *mJumpHeight_s;
}

void BackStepToTarget::m39() {
    sub_7100738428(mActor, *mStopSpeedRatio_s);
}

void BackStepToTarget::m40() {
    if (auto* controller = mActor->getCharacterController())
        sub_7100738660(controller, *mStopRotSpeedRatio_s);
}

void BackStepToTarget::m38() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_58 * 30.0f);
        sub_710072C1B4(controller, _a8);
    }
}

void BackStepToTarget::m33(sead::Vector3f* dir, const sead::Vector3f& up) {
    sead::Vector3f d = *mTargetPos_d - mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&d, d, up);
    d.normalize();
    *dir = d;
}

}  // namespace uking::action
