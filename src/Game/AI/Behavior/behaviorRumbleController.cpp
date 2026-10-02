#include "Game/AI/Behavior/behaviorRumbleController.h"

namespace uking::behavior {

RumbleController::RumbleController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RumbleController::~RumbleController() = default;

bool RumbleController::m6(sead::Heap* heap) {
    return true;
}

void RumbleController::m8() {}

void RumbleController::m9() {}

void RumbleController::loadParams() {
    getStaticParam(&mReduceDist_s, "ReduceDist");
}

}  // namespace uking::behavior
