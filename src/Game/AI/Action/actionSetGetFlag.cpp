#include "Game/AI/Action/actionSetGetFlag.h"

namespace uking::action {

SetGetFlag::SetGetFlag(const InitArg& arg) : SetGetFlagBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SetGetFlag::~SetGetFlag() {
    ;
}

bool SetGetFlag::init_(sead::Heap* heap) {
    return SetGetFlagBase::init_(heap);
}

void SetGetFlag::loadParams_() {
    SetGetFlagBase::loadParams_();
}

}  // namespace uking::action
