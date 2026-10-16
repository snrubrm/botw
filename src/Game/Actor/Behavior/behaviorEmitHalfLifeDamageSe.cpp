#include "Game/Actor/Behavior/behaviorEmitHalfLifeDamageSe.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

EmitHalfLifeDamageSe::EmitHalfLifeDamageSe(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EmitHalfLifeDamageSe::~EmitHalfLifeDamageSe() = default;

bool EmitHalfLifeDamageSe::init_(sead::Heap* heap) {
    return true;
}

void EmitHalfLifeDamageSe::leave() {}

void EmitHalfLifeDamageSe::loadParams() {

}

void EmitHalfLifeDamageSe::enter() {
    _28 = checkHpRate(mActor, 0.5f);
}

void EmitHalfLifeDamageSe::calc() {
    const bool half_life = checkHpRate(mActor, 0.5f);
    if (!_28 && half_life)
        xlinkSearchAndEmit(mActor, "DamageHalfLife", 2, nullptr);
    _28 = half_life;
}

}  // namespace uking::behavior
