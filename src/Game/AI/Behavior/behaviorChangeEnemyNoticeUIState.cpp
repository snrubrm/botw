#include "Game/AI/Behavior/behaviorChangeEnemyNoticeUIState.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void ChangeEnemyNoticeUIState::m8() {
    int key = *mKey_s;
    if (key == 4)
        key = 5;
    mActor->m93(key, 0.0f);
}

}  // namespace uking::behavior
