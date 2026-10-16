#include "Game/Actor/Behavior/behaviorEmitGanonHalfLifeDamageSe.h"
#include "Game/Actor/aiUnk_71002C52DC.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

EmitGanonHalfLifeDamageSe::EmitGanonHalfLifeDamageSe(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

EmitGanonHalfLifeDamageSe::~EmitGanonHalfLifeDamageSe() = default;

bool EmitGanonHalfLifeDamageSe::init_(sead::Heap* heap) {
    return true;
}

void EmitGanonHalfLifeDamageSe::calc() {
    const bool is_half_life = sub_71002C52DC(mActor, 0.5f);
    if (!_28 && is_half_life)
        xlinkSearchAndEmit(mActor, "DamageHalfLife", 2, nullptr);
    _28 = is_half_life;
}

void EmitGanonHalfLifeDamageSe::enter() {
    _28 = sub_71002C52DC(mActor, 0.5f);
}

void EmitGanonHalfLifeDamageSe::leave() {}

void EmitGanonHalfLifeDamageSe::loadParams() {

}

}  // namespace uking::behavior
