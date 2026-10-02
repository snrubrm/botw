#include "Game/AI/AI/aiNPCSuspend.h"

namespace uking::ai {

NPCSuspend::NPCSuspend(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCSuspend::~NPCSuspend() {
    ;
}

bool NPCSuspend::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSuspend::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = *mRetryCount_s;
    _6c = ksys::Timer(*mWaitTime_s, *mWaitTime_s);
    changeChild("停止");
}

void NPCSuspend::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCSuspend::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mEndMoveTime_s, "EndMoveTime");
    getStaticParam(&mRetryCount_s, "RetryCount");
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::ai
