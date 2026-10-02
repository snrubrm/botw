#include "Game/AI/AI/aiCollaborationShootingStarRoot.h"

namespace uking::ai {

CollaborationShootingStarRoot::CollaborationShootingStarRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps this class's vtable store, which a defaulted destructor drops. Written like
// upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
CollaborationShootingStarRoot::~CollaborationShootingStarRoot() {
    ;
}

bool CollaborationShootingStarRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CollaborationShootingStarRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CollaborationShootingStarRoot::leave_() {
    _58.fadeXLink();
}

void CollaborationShootingStarRoot::loadParams_() {
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    // FIXME: CALL _ZN4sead14SafeStringBaseIcEaSERKS1_ @ 0x7100b0caa0
    // FIXME: CALL _ZNK4sead14SafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL _ZN4sead9HashCRC3214calcStringHashEPKc @ 0x7100b2170c
}

}  // namespace uking::ai
