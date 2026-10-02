#include "Game/AI/Behavior/behaviorSyncASFrameToAnimalUnit.h"

namespace uking::behavior {

SyncASFrameToAnimalUnit::SyncASFrameToAnimalUnit(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SyncASFrameToAnimalUnit::~SyncASFrameToAnimalUnit() = default;

bool SyncASFrameToAnimalUnit::m6(sead::Heap* heap) {
    return true;
}

void SyncASFrameToAnimalUnit::m8() {}

void SyncASFrameToAnimalUnit::m9() {}

void SyncASFrameToAnimalUnit::loadParams() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

}  // namespace uking::behavior
