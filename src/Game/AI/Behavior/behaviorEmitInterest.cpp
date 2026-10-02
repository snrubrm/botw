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

// NON_MATCHING: the original reads both params before updating the unit (borderline fix in the log)
void EmitInterest::m7() {
    auto* unit = mActor->get548();
    if (!unit)
        return;
    const int level = *mLevel_s;
    if (unit->_18._48 < level)
        unit->_18._48 = level;
    unit->_18._44 |= *mIsTargetNPC_s;
}

}  // namespace uking::behavior
