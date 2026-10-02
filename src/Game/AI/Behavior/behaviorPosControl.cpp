#include "Game/AI/Behavior/behaviorPosControl.h"

namespace uking::behavior {

PosControl::PosControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

PosControl::~PosControl() = default;

bool PosControl::m6(sead::Heap* heap) {
    return true;
}

void PosControl::m8() {}

void PosControl::m9() {}

void PosControl::loadParams() {
    getStaticParam(&mImpulse_s, "Impulse");
}

}  // namespace uking::behavior
