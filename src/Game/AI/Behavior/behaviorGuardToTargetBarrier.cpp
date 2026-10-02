#include "Game/AI/Behavior/behaviorGuardToTargetBarrier.h"

namespace uking::behavior {

GuardToTargetBarrier::GuardToTargetBarrier(const InitArg& arg) : GuardFrontBarrier(arg) {}

GuardToTargetBarrier::~GuardToTargetBarrier() = default;

bool GuardToTargetBarrier::m6(sead::Heap* heap) {
    return GuardFrontBarrier::m6(heap);
}

void GuardToTargetBarrier::m7() {
    GuardFrontBarrier::m7();
}

void GuardToTargetBarrier::m8() {
    GuardFrontBarrier::m8();
}

void GuardToTargetBarrier::m9() {
    GuardFrontBarrier::m9();
}

void GuardToTargetBarrier::loadParams() {
    GuardFrontBarrier::loadParams();
}

}  // namespace uking::behavior
