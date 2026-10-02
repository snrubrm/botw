#include "Game/AI/Behavior/behaviorSetNoWeakHitReactionDCCallBack.h"

namespace uking::behavior {

SetNoWeakHitReactionDCCallBack::SetNoWeakHitReactionDCCallBack(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetNoWeakHitReactionDCCallBack::~SetNoWeakHitReactionDCCallBack() = default;

bool SetNoWeakHitReactionDCCallBack::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetNoWeakHitReactionDCCallBack::m7() {
    SetDamageCallback::m7();
}

void SetNoWeakHitReactionDCCallBack::m8() {
    SetDamageCallback::m8();
}

void SetNoWeakHitReactionDCCallBack::m9() {
    SetDamageCallback::m9();
}

void SetNoWeakHitReactionDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetNoWeakHitReactionDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
