#include "Game/Actor/Behavior/behaviorDisableBoneController.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::behavior {

DisableBoneController::DisableBoneController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableBoneController::~DisableBoneController() = default;

bool DisableBoneController::init_(sead::Heap* heap) {
    return true;
}

void DisableBoneController::enter() {}

void DisableBoneController::leave() {}

void DisableBoneController::loadParams() {

}

void DisableBoneController::calc() {
    sub_71005DB3EC(mActor);
}

}  // namespace uking::behavior
