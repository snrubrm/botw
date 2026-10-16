#include "Game/Actor/Behavior/behaviorElevatorBaseEmitPassingSe.h"

namespace uking::behavior {

ElevatorBaseEmitPassingSe::ElevatorBaseEmitPassingSe(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ElevatorBaseEmitPassingSe::~ElevatorBaseEmitPassingSe() = default;

bool ElevatorBaseEmitPassingSe::init_(sead::Heap* heap) {
    return true;
}

void ElevatorBaseEmitPassingSe::leave() {}

void ElevatorBaseEmitPassingSe::loadParams() {

}

}  // namespace uking::behavior
