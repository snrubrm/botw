#include "Game/AI/Behavior/behaviorBgmCtrlBehavior.h"

namespace uking::behavior {

BgmCtrlBehavior::BgmCtrlBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
BgmCtrlBehavior::~BgmCtrlBehavior() {
    ;
}

bool BgmCtrlBehavior::m6(sead::Heap* heap) {
    return true;
}

void BgmCtrlBehavior::m7() {}

void BgmCtrlBehavior::m9() {}

void BgmCtrlBehavior::loadParams() {
    getStaticParam(&mFadeTime_s, "FadeTime");
    getStaticParam(&mCtrlType_s, "CtrlType");
    getStaticParam(&mBgmName_s, "BgmName");
}

}  // namespace uking::behavior
