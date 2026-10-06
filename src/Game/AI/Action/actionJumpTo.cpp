#include "Game/AI/Action/actionJumpTo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"

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

// NON_MATCHING: regalloc of the up-direction components in the fallback path.
void JumpTo::m39() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sub_710073FA94(&_64, mActor);
    const sead::Vector3f dir = getUpDir(controller->get70());
    sub_710074006C(&_64, _88, dir, true, 0.1f, sead::Mathf::pi2(), 0.0f);
    sub_7100740E04(_64, controller);
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

f32 JumpTo::sub_71001C72EC() {
    f32 speed = 0.0f;
    f32 time = 0.0f;
    const sead::Vector3f start = mActor->getMtx().getTranslation();
    const sead::Vector3f target = *mParams.mTargetPos_d + m44();
    const sead::Vector3f gravity = getGravity(mActor) * (1.0f / 900.0f);
    if (!sub_710072CD88(*mParams.mJumpHeight_s, &speed, &time, &start, &target, &gravity))
        speed = *mParams.mMaxSpeed_s;
    return sead::Mathf::clampMax(speed, *mParams.mMaxSpeed_s);
}

// NON_MATCHING: the original copies _70 to a stack slot (memcpy-style) before normalising; ours
// keeps it in registers (register numbering and the operand order of the normalise multiplies differ).
void JumpTo::m42() {
    const f32 jump_gravity = *mParams.mJumpGravity_s;
    if (jump_gravity < 0.0f) {
        if (auto* controller = mActor->getCharacterController()) {
            sead::Vector3f dir = controller->get70();
            dir.normalize();
            dir *= -jump_gravity;
            controller->sub_7100F5EE1C(dir);
        }
    }
    _58.value = _58.prev_value = sub_71001C72EC();
    _58.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5E7F0(_58.value * 30.0f);
        sub_710072C1B4(controller, _88);
        controller->sub_7100F62B70(*mParams.mJumpHeight_s);
        controller->sub_7100F5EF08(true);
    }
}

}  // namespace uking::action
