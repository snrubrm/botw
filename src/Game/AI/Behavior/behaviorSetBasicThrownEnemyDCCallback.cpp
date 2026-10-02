#include "Game/AI/Behavior/behaviorSetBasicThrownEnemyDCCallback.h"

namespace uking::behavior {

SetBasicThrownEnemyDCCallback::SetBasicThrownEnemyDCCallback(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetBasicThrownEnemyDCCallback::~SetBasicThrownEnemyDCCallback() = default;

bool SetBasicThrownEnemyDCCallback::m6(sead::Heap* heap) {
    return true;
}

void SetBasicThrownEnemyDCCallback::m7() {}

void SetBasicThrownEnemyDCCallback::m8() {
    setDamageCallbackTiming(mActor, 4, &_28);
    setDamageCallbackTiming(mActor, 1, &_50);
    setDamageCallbackTiming(mActor, 3, &_78);
}

void SetBasicThrownEnemyDCCallback::m9() {
    sub_71005DA114(mActor, &_28);
    sub_71005DA114(mActor, &_50);
    sub_71005DA114(mActor, &_78);
}

void SetBasicThrownEnemyDCCallback::loadParams() {

}

}  // namespace uking::behavior
