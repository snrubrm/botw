#include "Game/AI/Behavior/behaviorEmitCreateDeleteEffect.h"

namespace uking::behavior {

EmitCreateDeleteEffect::EmitCreateDeleteEffect(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
EmitCreateDeleteEffect::~EmitCreateDeleteEffect() {
    ;
}

bool EmitCreateDeleteEffect::m6(sead::Heap* heap) {
    return true;
}

void EmitCreateDeleteEffect::m9() {}

void EmitCreateDeleteEffect::loadParams() {
    getStaticParam(&mEffectName_s, "EffectName");
}

}  // namespace uking::behavior
