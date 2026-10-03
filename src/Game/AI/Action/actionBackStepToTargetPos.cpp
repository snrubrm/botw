#include "Game/AI/Action/actionBackStepToTargetPos.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BackStepToTargetPos::BackStepToTargetPos(const InitArg& arg) : BackStepToTarget(arg) {}

BackStepToTargetPos::~BackStepToTargetPos() = default;

bool BackStepToTargetPos::init_(sead::Heap* heap) {
    return BackStepToTarget::init_(heap);
}

void BackStepToTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getTranslation(_108);
    BackStepToTarget::enter_(params);
}

void BackStepToTargetPos::leave_() {
    BackStepToTarget::leave_();
}

void BackStepToTargetPos::loadParams_() {
    BackStepToTarget::loadParams_();
    getStaticParam(&mIsJumpHeightFromHigherPos_s, "IsJumpHeightFromHigherPos");
    getStaticParam(&mStartAS_s, "StartAS");
    getStaticParam(&mLoopAS_s, "LoopAS");
    getStaticParam(&mPreLandAS_s, "PreLandAS");
    getStaticParam(&mEndAS_s, "EndAS");
}

void BackStepToTargetPos::calc_() {
    BackStepToTarget::calc_();
}

void BackStepToTargetPos::m34() {
    playAS(mStartAS_s.cstr(), false, 0, 0, -1.0f);
}

void BackStepToTargetPos::m35() {
    playAS(mLoopAS_s.cstr(), false, 0, 0, -1.0f);
}

void BackStepToTargetPos::m36() {
    playAS(mPreLandAS_s.cstr(), true, 0, 0, -1.0f);
}

void BackStepToTargetPos::m37() {
    playAS(mEndAS_s.cstr(), true, 0, 0, -1.0f);
}

// NON_MATCHING: the original keeps a branch on the height comparison (we get fcsel)
f32 BackStepToTargetPos::m42() {
    if (*mIsJumpHeightFromHigherPos_s) {
        const f32 y = mTargetPos_d->y;
        const f32 height = *mJumpHeight_s;
        if (_108.y >= y)
            return height;
        return y + height - _108.y;
    }
    return *mJumpHeight_s;
}

void BackStepToTargetPos::m33(sead::Vector3f* dir, const sead::Vector3f& up) {
    ksys::util::sub_71011EFA00(dir, _108 - *mTargetPos_d, up);
    dir->normalize();
}

}  // namespace uking::action
