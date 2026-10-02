#include "Game/AI/Behavior/behaviorNeckBattleMode.h"

namespace uking::behavior {

NeckBattleMode::NeckBattleMode(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NeckBattleMode::~NeckBattleMode() = default;

bool NeckBattleMode::m6(sead::Heap* heap) {
    return true;
}

void NeckBattleMode::m7() {}

void NeckBattleMode::loadParams() {

}

}  // namespace uking::behavior
