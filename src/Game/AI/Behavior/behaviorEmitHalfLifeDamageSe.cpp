#include "Game/AI/Behavior/behaviorEmitHalfLifeDamageSe.h"
#include "Game/AI/aiUnk_71007368A4.h"

namespace uking::behavior {

EmitHalfLifeDamageSe::EmitHalfLifeDamageSe(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EmitHalfLifeDamageSe::~EmitHalfLifeDamageSe() = default;

bool EmitHalfLifeDamageSe::m6(sead::Heap* heap) {
    return true;
}

void EmitHalfLifeDamageSe::m9() {}

void EmitHalfLifeDamageSe::loadParams() {

}

void EmitHalfLifeDamageSe::m8() {
    _28 = checkHpRate(mActor, 0.5f);
}

}  // namespace uking::behavior
