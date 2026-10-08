#include "Game/AI/Behavior/behaviorSetBasicThrownEnemyDCCallback.h"

namespace uking::behavior {

SetBasicThrownEnemyDCCallback::SetBasicThrownEnemyDCCallback(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetBasicThrownEnemyDCCallback::~SetBasicThrownEnemyDCCallback() = default;

bool SetBasicThrownEnemyDCCallback::m6(sead::Heap* heap) {
    return true;
}

void Unk_7102438e08::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 == 25)
        *a5 = 26;
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
