#include "Game/AI/Behavior/behaviorEmitInterest.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

EmitInterest::EmitInterest(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EmitInterest::~EmitInterest() = default;

bool EmitInterest::m6(sead::Heap* heap) {
    return true;
}

void EmitInterest::m8() {}

void EmitInterest::m9() {}

void EmitInterest::loadParams() {
    getStaticParam(&mLevel_s, "Level");
    getStaticParam(&mIsTargetNPC_s, "IsTargetNPC");
}

void EmitInterest::m7() {
    auto* unit = mActor->get548();
    if (!unit)
        return;
    unit->emitInterest(*mLevel_s, *mIsTargetNPC_s);
}

}  // namespace uking::behavior
