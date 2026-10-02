#include "Game/AI/Behavior/behaviorEmitHalfLifeDamageSe.h"

namespace uking::behavior {

EmitHalfLifeDamageSe::EmitHalfLifeDamageSe(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EmitHalfLifeDamageSe::~EmitHalfLifeDamageSe() = default;

bool EmitHalfLifeDamageSe::m6(sead::Heap* heap) {
    return true;
}

void EmitHalfLifeDamageSe::m9() {}

void EmitHalfLifeDamageSe::loadParams() {

}

}  // namespace uking::behavior
