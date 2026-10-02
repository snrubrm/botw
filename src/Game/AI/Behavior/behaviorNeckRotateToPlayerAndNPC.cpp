#include "Game/AI/Behavior/behaviorNeckRotateToPlayerAndNPC.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling (the 0x38 pair is stored first)
NeckRotateToPlayerAndNPC::NeckRotateToPlayerAndNPC(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

NeckRotateToPlayerAndNPC::~NeckRotateToPlayerAndNPC() = default;

bool NeckRotateToPlayerAndNPC::m6(sead::Heap* heap) {
    return true;
}

void NeckRotateToPlayerAndNPC::loadParams() {
    getStaticParam(&mUpdateInterval_s, "UpdateInterval");
    getStaticParam(&mLimitDistance_s, "LimitDistance");
    getStaticParam(&mLimitAngle_s, "LimitAngle");
    getStaticParam(&mIsUseAwnSight_s, "IsUseAwnSight");
}

}  // namespace uking::behavior
