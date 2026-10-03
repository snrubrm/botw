#include "Game/AI/Behavior/behaviorSpeedEmitInterest.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SpeedEmitInterest::SpeedEmitInterest(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SpeedEmitInterest::~SpeedEmitInterest() = default;

bool SpeedEmitInterest::m6(sead::Heap* heap) {
    return true;
}

void SpeedEmitInterest::m8() {}

void SpeedEmitInterest::m9() {}

void SpeedEmitInterest::loadParams() {
    getStaticParam(&mLevel_s, "Level");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mIsTargetNPC_s, "IsTargetNPC");
}

void SpeedEmitInterest::m7() {
    if (!(mActor->getVelocity().length() > *mSpeed_s))
        return;
    auto* unit = mActor->get548();
    unit->emitInterest(*mLevel_s, *mIsTargetNPC_s);
}

}  // namespace uking::behavior
