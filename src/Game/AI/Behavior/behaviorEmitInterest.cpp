#include "Game/AI/Behavior/behaviorEmitInterest.h"

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

}  // namespace uking::behavior
