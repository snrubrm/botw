#include "Game/AI/Behavior/behaviorEmitHalfLifeDamageSe.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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

void EmitHalfLifeDamageSe::m7() {
    const bool half_life = checkHpRate(mActor, 0.5f);
    if (!_28 && half_life)
        xlinkSearchAndEmit(mActor, "DamageHalfLife", 2, nullptr);
    _28 = half_life;
}

}  // namespace uking::behavior
