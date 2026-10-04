#include "Game/AI/Action/actionBackStepBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BackStepBase::BackStepBase(const InitArg& arg) : BackStepToTarget(arg) {}

BackStepBase::~BackStepBase() = default;

bool BackStepBase::init_(sead::Heap* heap) {
    return BackStepToTarget::init_(heap);
}

void BackStepBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BackStepToTarget::enter_(params);
}

void BackStepBase::leave_() {
    BackStepToTarget::leave_();
}

void BackStepBase::loadParams_() {
    BackStepToTarget::loadParams_();
    getStaticParam(&mJumpDist_s, "JumpDist");
}

void BackStepBase::calc_() {
    BackStepToTarget::calc_();
}

// NON_MATCHING: the original loads the translation into integer registers (copied to `target` after the
// normalize); ours loads x / z as floats
void BackStepBase::m41(f32* a, sead::Vector3f* b) {
    f32 time = 0.0f;
    const f32 gravity = *mJumpGravity_s / 900.0f;
    sead::Vector3f velocity;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f away = {pos.x - mTargetPos_d->x, 0.0f, pos.z - mTargetPos_d->z};
    away.normalize();
    sead::Vector3f target = pos;
    target += away * *mJumpDist_s;
    sub_71005DF66C(&velocity, mActor, &target, &time, *mJumpHeight_s, gravity);
    *a = velocity.normalize();
    *b = velocity;
}

}  // namespace uking::action
