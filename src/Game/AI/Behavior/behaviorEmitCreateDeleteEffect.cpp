#include "Game/AI/Behavior/behaviorEmitCreateDeleteEffect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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

void EmitCreateDeleteEffect::m8() {
    if (mActor->checkFlag(ksys::act::Actor::ActorFlag::_35) && !mEffectName_s.isEmpty())
        xlinkSearchAndEmit(mActor, mEffectName_s.cstr(), 2, nullptr);
}

void EmitCreateDeleteEffect::m7() {
    if (mActor->checkFlag(ksys::act::Actor::ActorFlag::_36) && !mEffectName_s.isEmpty())
        xlinkSearchAndEmit(mActor, mEffectName_s.cstr(), 2, nullptr);
}

}  // namespace uking::behavior
