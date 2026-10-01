#include "Game/AI/AI/aiCircleMoveInWater.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CircleMoveInWater::CircleMoveInWater(const InitArg& arg) : CircleMoveInFluid(arg) {}

CircleMoveInWater::~CircleMoveInWater() = default;

bool CircleMoveInWater::init_(sead::Heap* heap) {
    return CircleMoveInFluid::init_(heap);
}

void CircleMoveInWater::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMoveInFluid::enter_(params);
}

void CircleMoveInWater::calc_() {
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }

    if (depth < *mAllowMoveWaterDepth_s)
        _cc = !_cc;
    CircleMoveInFluid::calc_();
}

void CircleMoveInWater::leave_() {
    CircleMoveInFluid::leave_();
}

void CircleMoveInWater::loadParams_() {
    CircleMoveInFluid::loadParams_();
    getStaticParam(&mAllowMoveWaterDepth_s, "AllowMoveWaterDepth");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void CircleMoveInWater::m34() {}

void CircleMoveInWater::m36(sead::Vector3f* out) {
    out->set(*mTargetPos_d);
}

}  // namespace uking::ai
