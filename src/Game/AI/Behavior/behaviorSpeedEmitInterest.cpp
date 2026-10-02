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

// NON_MATCHING: the original reads both params before updating the unit (borderline fix in the log)
void SpeedEmitInterest::m7() {
    if (!(mActor->getVelocity().length() > *mSpeed_s))
        return;
    auto* unit = mActor->get548();
    const int level = *mLevel_s;
    if (unit->_18._48 < level)
        unit->_18._48 = level;
    unit->_18._44 |= *mIsTargetNPC_s;
}

}  // namespace uking::behavior
