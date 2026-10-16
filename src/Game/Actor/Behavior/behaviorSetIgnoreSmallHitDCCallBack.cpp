#include "Game/Actor/Behavior/behaviorSetIgnoreSmallHitDCCallBack.h"

namespace uking::behavior {

SetIgnoreSmallHitDCCallBack::SetIgnoreSmallHitDCCallBack(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetIgnoreSmallHitDCCallBack::~SetIgnoreSmallHitDCCallBack() = default;

bool SetIgnoreSmallHitDCCallBack::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetIgnoreSmallHitDCCallBack::calc() {
    SetDamageCallback::calc();
}

void SetIgnoreSmallHitDCCallBack::enter() {
    SetDamageCallback::enter();
}

void SetIgnoreSmallHitDCCallBack::leave() {
    SetDamageCallback::leave();
}

void SetIgnoreSmallHitDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::act::DamageCallback* SetIgnoreSmallHitDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
