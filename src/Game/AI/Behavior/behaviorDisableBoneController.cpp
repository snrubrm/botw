#include "Game/AI/Behavior/behaviorDisableBoneController.h"
#include "Game/AI/aiUnk_71005D6D10.h"

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

void DisableBoneController::m7() {
    sub_71005DB3EC(mActor);
}

}  // namespace uking::behavior
