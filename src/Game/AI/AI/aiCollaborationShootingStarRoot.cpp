#include "Game/AI/AI/aiCollaborationShootingStarRoot.h"
#include <codec/seadHashCRC32.h>

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
    const sead::SafeString id = mCollaboShootingStarId_a->cstr();
    _48 = id;
    _40 = sead::HashCRC32::calcStringHash(id.cstr());
}

}  // namespace uking::ai
