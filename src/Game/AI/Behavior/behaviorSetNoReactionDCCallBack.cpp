#include "Game/AI/Behavior/behaviorSetNoReactionDCCallBack.h"

namespace uking::behavior {

SetNoReactionDCCallBack::SetNoReactionDCCallBack(const InitArg& arg) : SetDamageCallback(arg) {}

SetNoReactionDCCallBack::~SetNoReactionDCCallBack() = default;

bool SetNoReactionDCCallBack::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetNoReactionDCCallBack::m7() {
    SetDamageCallback::m7();
}

void SetNoReactionDCCallBack::m8() {
    SetDamageCallback::m8();
}

void SetNoReactionDCCallBack::m9() {
    SetDamageCallback::m9();
}

void SetNoReactionDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetNoReactionDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
