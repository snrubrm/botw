#include "Game/AI/Behavior/behaviorGuardTgtControl.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

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

void GuardTgtControl::m8() {
    _38 = false;
    sub_71007A3910(mActor, mGuardTgtName_s.cstr());
}

void GuardTgtControl::m9() {
    sub_71007A3910(mActor, mGuardTgtName_s.cstr());
}

}  // namespace uking::behavior
