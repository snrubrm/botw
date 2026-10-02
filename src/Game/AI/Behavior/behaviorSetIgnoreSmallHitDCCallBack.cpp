#include "Game/AI/Behavior/behaviorSetIgnoreSmallHitDCCallBack.h"

namespace uking::behavior {

SetIgnoreSmallHitDCCallBack::SetIgnoreSmallHitDCCallBack(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetIgnoreSmallHitDCCallBack::~SetIgnoreSmallHitDCCallBack() = default;

bool SetIgnoreSmallHitDCCallBack::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetIgnoreSmallHitDCCallBack::m7() {
    SetDamageCallback::m7();
}

void SetIgnoreSmallHitDCCallBack::m8() {
    SetDamageCallback::m8();
}

void SetIgnoreSmallHitDCCallBack::m9() {
    SetDamageCallback::m9();
}

void SetIgnoreSmallHitDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetIgnoreSmallHitDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
