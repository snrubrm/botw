#include "Game/AI/Action/actionNPCTargetMoveDynAs.h"

namespace uking::action {

NPCTargetMoveDynAs::NPCTargetMoveDynAs(const InitArg& arg) : NPCTargetMove(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
NPCTargetMoveDynAs::~NPCTargetMoveDynAs() {
    ;
}

void NPCTargetMoveDynAs::loadParams_() {
    NPCTargetMove::loadParams_();
    getDynamicParam(&mDynASKeyName_d, "DynASKeyName");
}

}  // namespace uking::action
