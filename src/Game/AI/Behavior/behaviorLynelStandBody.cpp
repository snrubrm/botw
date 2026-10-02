#include "Game/AI/Behavior/behaviorLynelStandBody.h"

namespace uking::behavior {

LynelStandBody::LynelStandBody(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

LynelStandBody::~LynelStandBody() = default;

bool LynelStandBody::m6(sead::Heap* heap) {
    return true;
}

void LynelStandBody::m7() {}

void LynelStandBody::loadParams() {
    getStaticParam(&mStandRatioFB_s, "StandRatioFB");
    getStaticParam(&mStandRatioLR_s, "StandRatioLR");
    getAITreeVariable(&mLynelBodyControlUnit_a, "LynelBodyControlUnit");
}

}  // namespace uking::behavior
