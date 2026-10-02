#include "Game/AI/Behavior/behaviorSandwormBgmControl.h"

namespace uking::behavior {

SandwormBgmControl::SandwormBgmControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SandwormBgmControl::~SandwormBgmControl() = default;

bool SandwormBgmControl::m6(sead::Heap* heap) {
    return true;
}

void SandwormBgmControl::loadParams() {
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mIsEnable_s, "IsEnable");
}

}  // namespace uking::behavior
