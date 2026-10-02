#include "Game/AI/Behavior/behaviorSetFixedNoActionDCCallBack.h"

namespace uking::behavior {

SetFixedNoActionDCCallBack::SetFixedNoActionDCCallBack(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetFixedNoActionDCCallBack::~SetFixedNoActionDCCallBack() = default;

bool SetFixedNoActionDCCallBack::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetFixedNoActionDCCallBack::m7() {
    SetDamageCallback::m7();
}

void SetFixedNoActionDCCallBack::m8() {
    SetDamageCallback::m8();
}

void SetFixedNoActionDCCallBack::m9() {
    SetDamageCallback::m9();
}

void SetFixedNoActionDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetFixedNoActionDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
