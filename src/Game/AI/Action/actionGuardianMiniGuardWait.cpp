#include "Game/AI/Action/actionGuardianMiniGuardWait.h"

namespace uking::action {

GuardianMiniGuardWait::GuardianMiniGuardWait(const InitArg& arg) : GuardianMiniWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GuardianMiniGuardWait::~GuardianMiniGuardWait() {
    ;
}

void GuardianMiniGuardWait::loadParams_() {
    GuardianMiniWait::loadParams_();
    getStaticParam(&mGuardASName_s, "GuardASName");
}

}  // namespace uking::action
