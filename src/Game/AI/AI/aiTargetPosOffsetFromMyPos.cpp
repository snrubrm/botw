#include "Game/AI/AI/aiTargetPosOffsetFromMyPos.h"

namespace uking::ai {

TargetPosOffsetFromMyPos::TargetPosOffsetFromMyPos(const InitArg& arg) : TargetPosOffset(arg) {}

TargetPosOffsetFromMyPos::~TargetPosOffsetFromMyPos() = default;

bool TargetPosOffsetFromMyPos::init_(sead::Heap* heap) {
    return TargetPosOffset::init_(heap);
}

void TargetPosOffsetFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosOffset::enter_(params);
}

void TargetPosOffsetFromMyPos::calc_() {
    TargetPosOffset::calc_();
}

void TargetPosOffsetFromMyPos::leave_() {
    TargetPosOffset::leave_();
}

void TargetPosOffsetFromMyPos::loadParams_() {
    TargetPosOffset::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TargetPosOffsetFromMyPos::m36(sead::Vector3f* pos) {
    *pos = *mTargetPos_d;
}

}  // namespace uking::ai
