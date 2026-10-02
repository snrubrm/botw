#include "Game/AI/AI/aiPriestBossActorCloneRoot.h"

namespace uking::ai {

PriestBossActorCloneRoot::PriestBossActorCloneRoot(const InitArg& arg)
    : PriestBossActorNormalRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PriestBossActorCloneRoot::~PriestBossActorCloneRoot() {
    ;
}

bool PriestBossActorCloneRoot::init_(sead::Heap* heap) {
    return PriestBossActorNormalRoot::init_(heap);
}

void PriestBossActorCloneRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorNormalRoot::enter_(params);
}

void PriestBossActorCloneRoot::leave_() {
    PriestBossActorNormalRoot::leave_();
}

void PriestBossActorCloneRoot::loadParams_() {
    PriestBossActorNormalRoot::loadParams_();
    getStaticParam(&mDisappearXLinkEventKey_s, "DisappearXLinkEventKey");
}

}  // namespace uking::ai
