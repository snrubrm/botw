#include "Game/AI/Behavior/behaviorEmitGanonHalfLifeDamageSe.h"

namespace uking::behavior {

EmitGanonHalfLifeDamageSe::EmitGanonHalfLifeDamageSe(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

EmitGanonHalfLifeDamageSe::~EmitGanonHalfLifeDamageSe() = default;

bool EmitGanonHalfLifeDamageSe::m6(sead::Heap* heap) {
    return true;
}

void EmitGanonHalfLifeDamageSe::m9() {}

void EmitGanonHalfLifeDamageSe::loadParams() {

}

}  // namespace uking::behavior
