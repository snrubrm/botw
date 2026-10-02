#include "Game/AI/Behavior/behaviorChangeEnemyNoticeUIState.h"

namespace uking::behavior {

ChangeEnemyNoticeUIState::ChangeEnemyNoticeUIState(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ChangeEnemyNoticeUIState::~ChangeEnemyNoticeUIState() = default;

bool ChangeEnemyNoticeUIState::m6(sead::Heap* heap) {
    return true;
}

void ChangeEnemyNoticeUIState::m7() {}

void ChangeEnemyNoticeUIState::m9() {}

void ChangeEnemyNoticeUIState::loadParams() {
    getStaticParam(&mKey_s, "Key");
}

}  // namespace uking::behavior
