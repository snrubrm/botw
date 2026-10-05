#include "Game/AI/Action/actionJumpTo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

JumpTo::JumpTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpTo::~JumpTo() = default;

bool JumpTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void JumpTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpTo::leave_() {
    ksys::act::ai::Action::leave_();
}

void JumpTo::loadParams_() {
    getStaticParam(&mParams.mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getStaticParam(&mParams.mJumpGravity_s, "JumpGravity");
    getStaticParam(&mParams.mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mParams.mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mParams.mInWaterDepth_s, "InWaterDepth");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void JumpTo::calc_() {
    ksys::act::ai::Action::calc_();
}

bool JumpTo::m35() {
    return true;
}

bool JumpTo::m36() {
    return true;
}

bool JumpTo::m37() {
    return true;
}

void JumpTo::m43() {}

const sead::Vector3f& JumpTo::m44() {
    return sead::Vector3f::zero;
}

void JumpTo::m41() {
    if (auto* controller = mActor->getCharacterController())
        sub_7100738660(controller, *mParams.mRotReduceRatioOnGround_s);
}

void JumpTo::m38() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_58.value * 30.0f);
        sub_710072C1B4(controller, _88);
    }
}

void JumpTo::m40() {
    if (auto* controller = mActor->getCharacterController()) {
        _58 *= *mParams.mPosReduceRatioOnGround_s;
        _58.updateStats();
        controller->sub_7100F5E7F0(_58.value * 30.0f);
        sub_710072C1B4(controller, _88);
    }
}

// NON_MATCHING: natural surface-height and matrix-Y load order differs.
bool JumpTo::sub_71001C72A8() const {
    const f32 threshold = *mParams.mInWaterDepth_s;
    if (!(threshold >= 0.0f))
        return false;
    const f32 depth = mActor->get68f() ? mActor->get6f0() - mActor->getMtx().m[1][3] : 0.0f;
    return depth >= threshold;
}

}  // namespace uking::action
