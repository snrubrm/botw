#include "Game/AI/AI/aiTargetPosAnchorOffsetTarget.h"

namespace uking::ai {

TargetPosAnchorOffsetTarget::TargetPosAnchorOffsetTarget(const InitArg& arg) : TargetPosAI(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
TargetPosAnchorOffsetTarget::~TargetPosAnchorOffsetTarget() {
    ;
}

bool TargetPosAnchorOffsetTarget::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosAnchorOffsetTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosAnchorOffsetTarget::calc_() {
    TargetPosAI::calc_();
}

void TargetPosAnchorOffsetTarget::leave_() {
    TargetPosAI::leave_();
}

void TargetPosAnchorOffsetTarget::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai
