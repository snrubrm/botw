#include "Game/Actor/Behavior/behaviorSetFixedNoActionDCCallBack.h"

namespace uking::behavior {

SetFixedNoActionDCCallBack::SetFixedNoActionDCCallBack(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetFixedNoActionDCCallBack::~SetFixedNoActionDCCallBack() = default;

bool SetFixedNoActionDCCallBack::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetFixedNoActionDCCallBack::calc() {
    SetDamageCallback::calc();
}

void SetFixedNoActionDCCallBack::enter() {
    SetDamageCallback::enter();
}

void SetFixedNoActionDCCallBack::leave() {
    SetDamageCallback::leave();
}

void SetFixedNoActionDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetFixedNoActionDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
