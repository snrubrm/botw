#include "Game/AI/Behavior/behaviorPlayASWithBurnState.h"

namespace uking::behavior {

PlayASWithBurnState::PlayASWithBurnState(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
PlayASWithBurnState::~PlayASWithBurnState() {
    ;
}

bool PlayASWithBurnState::m6(sead::Heap* heap) {
    return true;
}

void PlayASWithBurnState::m9() {}

void PlayASWithBurnState::loadParams() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mOnWaitASName_s, "OnWaitASName");
    getStaticParam(&mOnToOffASName_s, "OnToOffASName");
    getStaticParam(&mOffToOnASName_s, "OffToOnASName");
}

}  // namespace uking::behavior
