#include "Game/Actor/Behavior/behaviorEmitInterest.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

EmitInterest::EmitInterest(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EmitInterest::~EmitInterest() = default;

bool EmitInterest::init_(sead::Heap* heap) {
    return true;
}

void EmitInterest::enter() {}

void EmitInterest::leave() {}

void EmitInterest::loadParams() {
    getStaticParam(&mLevel_s, "Level");
    getStaticParam(&mIsTargetNPC_s, "IsTargetNPC");
}

void EmitInterest::calc() {
    auto* unit = mActor->get548();
    if (!unit)
        return;
    unit->emitInterest(*mLevel_s, *mIsTargetNPC_s);
}

}  // namespace uking::behavior
