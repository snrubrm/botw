#include "Game/AI/Behavior/behaviorAwnHearingParamChange.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling (the original zeroes the parameter pointers and the request before the vptr store)
AwnHearingParamChange::AwnHearingParamChange(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AwnHearingParamChange::~AwnHearingParamChange() = default;

bool AwnHearingParamChange::m6(sead::Heap* heap) {
    return true;
}

void AwnHearingParamChange::m7() {}

void AwnHearingParamChange::loadParams() {
    getStaticParam(&mNoticeRatio_s, "NoticeRatio");
    getStaticParam(&mWarnRatio_s, "WarnRatio");
}

// NON_MATCHING: the original copies the request fields in descending order (`_18`, `_10`, `_8`/`_c`) after the vptr
void AwnHearingParamChange::m8() {
    if (auto* awareness = mActor->getAwareness()) {
        if (auto* sensor = awareness->_260[1])
            sensor->m5(&_38);

        Unk_71023e2750 request = _38;
        if (*mNoticeRatio_s >= 0)
            request._1c = *mNoticeRatio_s;
        if (*mWarnRatio_s >= 0)
            request._18 = *mWarnRatio_s;
        awareness->sub_7100D7E6F4(&request, 1);
    }
}

void AwnHearingParamChange::m9() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7E6F4(&_38, 1);
}

}  // namespace uking::behavior
