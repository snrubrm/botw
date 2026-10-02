#include "Game/AI/Behavior/behaviorDisableBoneController.h"

namespace uking::behavior {

DisableBoneController::DisableBoneController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableBoneController::~DisableBoneController() = default;

bool DisableBoneController::m6(sead::Heap* heap) {
    return true;
}

void DisableBoneController::m8() {}

void DisableBoneController::m9() {}

void DisableBoneController::loadParams() {

}

}  // namespace uking::behavior
