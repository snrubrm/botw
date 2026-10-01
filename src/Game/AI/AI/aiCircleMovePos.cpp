#include "Game/AI/AI/aiCircleMovePos.h"

namespace uking::ai {

CircleMovePos::CircleMovePos(const InitArg& arg) : CircleMove(arg) {}

CircleMovePos::~CircleMovePos() = default;

bool CircleMovePos::init_(sead::Heap* heap) {
    return CircleMove::init_(heap);
}

void CircleMovePos::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMove::enter_(params);
}

void CircleMovePos::calc_() {
    CircleMove::calc_();
}

void CircleMovePos::leave_() {
    CircleMove::leave_();
}

void CircleMovePos::loadParams_() {
    CircleMove::loadParams_();
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

void CircleMovePos::m34(sead::Vector3f* out) {
    if (out)
        out->set(*mCentralPos_d);
}

}  // namespace uking::ai
