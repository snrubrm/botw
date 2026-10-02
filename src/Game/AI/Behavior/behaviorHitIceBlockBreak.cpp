#include "Game/AI/Behavior/behaviorHitIceBlockBreak.h"

namespace uking::behavior {

HitIceBlockBreak::HitIceBlockBreak(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
HitIceBlockBreak::~HitIceBlockBreak() {
    ;
}

void HitIceBlockBreak::m8() {}

void HitIceBlockBreak::m9() {}

void HitIceBlockBreak::loadParams() {
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

}  // namespace uking::behavior
