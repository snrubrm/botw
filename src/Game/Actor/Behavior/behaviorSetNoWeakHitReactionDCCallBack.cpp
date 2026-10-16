#include "Game/Actor/Behavior/behaviorSetNoWeakHitReactionDCCallBack.h"

namespace uking::behavior {

SetNoWeakHitReactionDCCallBack::SetNoWeakHitReactionDCCallBack(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetNoWeakHitReactionDCCallBack::~SetNoWeakHitReactionDCCallBack() = default;

bool SetNoWeakHitReactionDCCallBack::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetNoWeakHitReactionDCCallBack::calc() {
    SetDamageCallback::calc();
}

void SetNoWeakHitReactionDCCallBack::enter() {
    SetDamageCallback::enter();
}

void SetNoWeakHitReactionDCCallBack::leave() {
    SetDamageCallback::leave();
}

void SetNoWeakHitReactionDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetNoWeakHitReactionDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
