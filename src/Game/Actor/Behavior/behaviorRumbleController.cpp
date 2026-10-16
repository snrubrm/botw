#include "Game/Actor/Behavior/behaviorRumbleController.h"

namespace uking::behavior {

RumbleController::RumbleController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RumbleController::~RumbleController() = default;

bool RumbleController::init_(sead::Heap* heap) {
    return true;
}

void RumbleController::enter() {}

void RumbleController::leave() {}

void RumbleController::loadParams() {
    getStaticParam(&mReduceDist_s, "ReduceDist");
}

}  // namespace uking::behavior
