#include "Game/AI/Behavior/behaviorAwnHearingParamChange.h"

namespace uking::behavior {

// NON_MATCHING: the awareness parameter object at 0x38 is not declared yet (placeholder bytes)
AwnHearingParamChange::AwnHearingParamChange(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool AwnHearingParamChange::m6(sead::Heap* heap) {
    return true;
}

void AwnHearingParamChange::m7() {}

void AwnHearingParamChange::loadParams() {
    getStaticParam(&mNoticeRatio_s, "NoticeRatio");
    getStaticParam(&mWarnRatio_s, "WarnRatio");
}

}  // namespace uking::behavior
