#include "Game/AI/Action/actionNPCWaitDynAS.h"

namespace uking::action {

NPCWaitDynAS::NPCWaitDynAS(const InitArg& arg) : NPCWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
NPCWaitDynAS::~NPCWaitDynAS() {
    ;
}

void NPCWaitDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCWait::enter_(params);
}

const sead::SafeString& NPCWaitDynAS::m32() {
    return mDynASName_d;
}

void NPCWaitDynAS::loadParams_() {
    NPCWait::loadParams_();
    getDynamicParam(&mDynASName_d, "DynASName");
}

}  // namespace uking::action
