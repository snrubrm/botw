#include "Game/AI/Behavior/behaviorGuardTgtControl.h"

namespace uking::behavior {

GuardTgtControl::GuardTgtControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GuardTgtControl::~GuardTgtControl() {
    ;
}

void GuardTgtControl::loadParams() {
    getStaticParam(&mGuardTgtName_s, "GuardTgtName");
}

}  // namespace uking::behavior
