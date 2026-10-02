#include "Game/AI/Action/actionJumpToTargetFromWater.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

JumpToTargetFromWater::JumpToTargetFromWater(const InitArg& arg) : JumpTo(arg) {}

JumpToTargetFromWater::~JumpToTargetFromWater() = default;

bool JumpToTargetFromWater::init_(sead::Heap* heap) {
    return JumpTo::init_(heap);
}

void JumpToTargetFromWater::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTo::enter_(params);
}

void JumpToTargetFromWater::leave_() {
    JumpTo::leave_();
    _e8.resetMotionType(mActor->getCharacterController());
}

void JumpToTargetFromWater::loadParams_() {
    JumpTo::loadParams_();
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mPreJumpAS_s, "PreJumpAS");
    getStaticParam(&mJumpAS_s, "JumpAS");
    getStaticParam(&mLandAS_s, "LandAS");
}

void JumpToTargetFromWater::calc_() {
    JumpTo::calc_();
}

void JumpToTargetFromWater::m32() {
    playAS(mPreJumpAS_s.cstr(), false, 0, 0, -1.0f);
}

void JumpToTargetFromWater::m33() {
    playAS(mJumpAS_s.cstr(), false, 0, 0, -1.0f);
}

void JumpToTargetFromWater::m34() {
    playAS(mLandAS_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
