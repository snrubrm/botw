#include "Game/Actor/AI/aiTargetPosAnchorOffsetTarget.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::ai {

TargetPosAnchorOffsetTarget::TargetPosAnchorOffsetTarget(const InitArg& arg) : TargetActorPos(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
TargetPosAnchorOffsetTarget::~TargetPosAnchorOffsetTarget() {
    ;
}

bool TargetPosAnchorOffsetTarget::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPosAnchorOffsetTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPosAnchorOffsetTarget::calc_() {
    TargetActorPos::calc_();
}

void TargetPosAnchorOffsetTarget::leave_() {
    TargetActorPos::leave_();
}

void TargetPosAnchorOffsetTarget::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

void TargetPosAnchorOffsetTarget::m35(sead::Vector3f* pos) {
    sub_71005DF270(pos, mActor, mAnchorName_s, *mDist_s);
}

}  // namespace uking::ai
