#include "Game/AI/AI/aiCircleMoveFlying.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CircleMoveFlying::CircleMoveFlying(const InitArg& arg) : CircleMoveInFluid(arg) {}

CircleMoveFlying::~CircleMoveFlying() = default;

bool CircleMoveFlying::init_(sead::Heap* heap) {
    return CircleMoveInFluid::init_(heap);
}

void CircleMoveFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMoveInFluid::enter_(params);
}

void CircleMoveFlying::calc_() {
    CircleMoveInFluid::calc_();
}

void CircleMoveFlying::leave_() {
    CircleMoveInFluid::leave_();
}

void CircleMoveFlying::loadParams_() {
    CircleMoveInFluid::loadParams_();
    getStaticParam(&mIsCheckSafetyAreaRadius_s, "IsCheckSafetyAreaRadius");
    getStaticParam(&mIsUseHomePos_s, "IsUseHomePos");
}

void CircleMoveFlying::m34() {
    sead::Vector3f pos;
    if (*mIsUseHomePos_s)
        mActor->getHomePos(&pos);
    else
        mActor->getMtx().getTranslation(pos);
    _a8 = pos;
}

void CircleMoveFlying::m35(f32 a2, f32 a3, f32 a4) {
    const f32 height = *CircleMoveInFluid::mParams.mRandRangeY_s + *CircleMoveInFluid::mParams.mRandRangeYOffest_s;
    const f32 max = std::sqrt(height * height + 29.0f * 29.0f);
    _b4 = sead::Mathf::min(a2, max) * a4;
    _b8 = sead::Mathf::min(a3, max) * a4;
}

}  // namespace uking::ai
