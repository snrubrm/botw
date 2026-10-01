#include "Game/AI/AI/aiCircleMoveTarget.h"

namespace uking::ai {

CircleMoveTarget::CircleMoveTarget(const InitArg& arg) : CircleMove(arg) {}

CircleMoveTarget::~CircleMoveTarget() = default;

bool CircleMoveTarget::init_(sead::Heap* heap) {
    return CircleMove::init_(heap);
}

void CircleMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMove::enter_(params);
}

void CircleMoveTarget::calc_() {
    CircleMove::calc_();
}

void CircleMoveTarget::leave_() {
    CircleMove::leave_();
}

void CircleMoveTarget::loadParams_() {
    CircleMove::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void CircleMoveTarget::m34(sead::Vector3f* out) {
    if (out)
        out->set(*mTargetPos_d);
}

}  // namespace uking::ai
