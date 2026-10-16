#include "Game/Actor/Behavior/behaviorSetNoReactionDCCallBack.h"

namespace uking::behavior {

SetNoReactionDCCallBack::SetNoReactionDCCallBack(const InitArg& arg) : SetDamageCallback(arg) {}

SetNoReactionDCCallBack::~SetNoReactionDCCallBack() = default;

bool SetNoReactionDCCallBack::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetNoReactionDCCallBack::calc() {
    SetDamageCallback::calc();
}

void SetNoReactionDCCallBack::enter() {
    SetDamageCallback::enter();
}

void SetNoReactionDCCallBack::leave() {
    SetDamageCallback::leave();
}

void SetNoReactionDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetNoReactionDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
