#include "Game/AI/Behavior/behaviorSyncBodyASAndAnimalUnitAS.h"

namespace uking::behavior {

// NON_MATCHING: the object at 0x28 is not declared yet (placeholder bytes)
SyncBodyASAndAnimalUnitAS::SyncBodyASAndAnimalUnitAS(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

bool SyncBodyASAndAnimalUnitAS::m6(sead::Heap* heap) {
    return true;
}

void SyncBodyASAndAnimalUnitAS::m7() {}

void SyncBodyASAndAnimalUnitAS::loadParams() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mPreFix_s, "PreFix");
}

}  // namespace uking::behavior
