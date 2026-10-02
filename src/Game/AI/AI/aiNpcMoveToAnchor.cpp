#include "Game/AI/AI/aiNpcMoveToAnchor.h"

namespace uking::ai {

NpcMoveToAnchor::NpcMoveToAnchor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NpcMoveToAnchor::~NpcMoveToAnchor() {
    ;
}

bool NpcMoveToAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NpcMoveToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NpcMoveToAnchor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NpcMoveToAnchor::loadParams_() {
    getDynamicParam(&mIsTurnToAnchorDir_d, "IsTurnToAnchorDir");
    getDynamicParam(&mIsAlignmentAnchor_d, "IsAlignmentAnchor");
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mAnchorUniqueName_d, "AnchorUniqueName");
    getDynamicParam(&mASKeyName_d, "ASKeyName");
}

}  // namespace uking::ai
