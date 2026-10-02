#include "Game/AI/Behavior/behaviorLynelBodyFitToGroundNormal.h"

namespace uking::behavior {

LynelBodyFitToGroundNormal::LynelBodyFitToGroundNormal(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

LynelBodyFitToGroundNormal::~LynelBodyFitToGroundNormal() = default;

bool LynelBodyFitToGroundNormal::m6(sead::Heap* heap) {
    return true;
}

void LynelBodyFitToGroundNormal::m7() {}

void LynelBodyFitToGroundNormal::loadParams() {
    getStaticParam(&mCorrectAngleMax_s, "CorrectAngleMax");
    getAITreeVariable(&mLynelBodyControlUnit_a, "LynelBodyControlUnit");
}

}  // namespace uking::behavior
