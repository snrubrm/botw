#include "Game/AI/Action/actionForkASPlay.h"

namespace uking::action {

ForkASPlay::ForkASPlay(const InitArg& arg) : ForkASPlayBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkASPlay::~ForkASPlay() {
    ;
}

void ForkASPlay::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

const char* ForkASPlay::m32() {
    return mASName_s.cstr();
}

}  // namespace uking::action
