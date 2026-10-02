#include "Game/AI/Behavior/behaviorCreateEaselBase.h"

namespace uking::behavior {

CreateEaselBase::CreateEaselBase(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
CreateEaselBase::~CreateEaselBase() {
    ;
}

void CreateEaselBase::m8() {}

void CreateEaselBase::m9() {}

void CreateEaselBase::loadParams() {
    getStaticParam(&mIsNoSystemDelete_s, "IsNoSystemDelete");
    getStaticParam(&mActorName_s, "ActorName");
    getStaticParam(&mOffset_s, "Offset");
}

const char* CreateEaselBase::m14() {
    return mActorName_s.cstr();
}

}  // namespace uking::behavior
