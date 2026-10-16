#include "Game/Actor/Behavior/behaviorSetIgnoreDrownDCCallBack.h"

namespace uking::behavior {

SetIgnoreDrownDCCallBack::SetIgnoreDrownDCCallBack(const InitArg& arg) : SetDamageCallback(arg) {}

SetIgnoreDrownDCCallBack::~SetIgnoreDrownDCCallBack() = default;

bool SetIgnoreDrownDCCallBack::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetIgnoreDrownDCCallBack::calc() {
    SetDamageCallback::calc();
}

void SetIgnoreDrownDCCallBack::enter() {
    SetDamageCallback::enter();
}

void SetIgnoreDrownDCCallBack::leave() {
    SetDamageCallback::leave();
}

void SetIgnoreDrownDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetIgnoreDrownDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
