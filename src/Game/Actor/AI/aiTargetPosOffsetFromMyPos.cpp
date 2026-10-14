#include "Game/Actor/AI/aiTargetPosOffsetFromMyPos.h"

namespace uking::ai {

TargetPosOffsetFromMyPos::TargetPosOffsetFromMyPos(const InitArg& arg) : OffsetTargetPos(arg) {}

TargetPosOffsetFromMyPos::~TargetPosOffsetFromMyPos() = default;

bool TargetPosOffsetFromMyPos::init_(sead::Heap* heap) {
    return OffsetTargetPos::init_(heap);
}

void TargetPosOffsetFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    OffsetTargetPos::enter_(params);
}

void TargetPosOffsetFromMyPos::calc_() {
    OffsetTargetPos::calc_();
}

void TargetPosOffsetFromMyPos::leave_() {
    OffsetTargetPos::leave_();
}

void TargetPosOffsetFromMyPos::loadParams_() {
    OffsetTargetPos::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TargetPosOffsetFromMyPos::m36(sead::Vector3f* pos) {
    *pos = *mTargetPos_d;
}

}  // namespace uking::ai
