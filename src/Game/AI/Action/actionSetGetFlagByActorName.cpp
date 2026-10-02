#include "Game/AI/Action/actionSetGetFlagByActorName.h"

namespace uking::action {

SetGetFlagByActorName::SetGetFlagByActorName(const InitArg& arg) : SetGetFlagBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SetGetFlagByActorName::~SetGetFlagByActorName() {
    ;
}

bool SetGetFlagByActorName::init_(sead::Heap* heap) {
    return SetGetFlagBase::init_(heap);
}

void SetGetFlagByActorName::loadParams_() {
    SetGetFlagBase::loadParams_();
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
