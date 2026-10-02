#include "Game/AI/Behavior/behaviorSetInfRotSpeedToSpineController.h"

namespace uking::behavior {

SetInfRotSpeedToSpineController::SetInfRotSpeedToSpineController(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetInfRotSpeedToSpineController::~SetInfRotSpeedToSpineController() = default;

bool SetInfRotSpeedToSpineController::m6(sead::Heap* heap) {
    return true;
}

void SetInfRotSpeedToSpineController::m7() {}

void SetInfRotSpeedToSpineController::loadParams() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

}  // namespace uking::behavior
