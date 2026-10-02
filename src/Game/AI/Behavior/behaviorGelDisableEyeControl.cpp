#include "Game/AI/Behavior/behaviorGelDisableEyeControl.h"

namespace uking::behavior {

GelDisableEyeControl::GelDisableEyeControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

GelDisableEyeControl::~GelDisableEyeControl() = default;

bool GelDisableEyeControl::m6(sead::Heap* heap) {
    return true;
}

void GelDisableEyeControl::m7() {}

void GelDisableEyeControl::loadParams() {
    getStaticParam(&mIsImmediate_s, "IsImmediate");
}

}  // namespace uking::behavior
