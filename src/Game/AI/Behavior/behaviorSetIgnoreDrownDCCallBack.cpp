#include "Game/AI/Behavior/behaviorSetIgnoreDrownDCCallBack.h"

namespace uking::behavior {

SetIgnoreDrownDCCallBack::SetIgnoreDrownDCCallBack(const InitArg& arg) : SetDamageCallback(arg) {}

SetIgnoreDrownDCCallBack::~SetIgnoreDrownDCCallBack() = default;

bool SetIgnoreDrownDCCallBack::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetIgnoreDrownDCCallBack::m7() {
    SetDamageCallback::m7();
}

void SetIgnoreDrownDCCallBack::m8() {
    SetDamageCallback::m8();
}

void SetIgnoreDrownDCCallBack::m9() {
    SetDamageCallback::m9();
}

void SetIgnoreDrownDCCallBack::loadParams() {
    SetDamageCallback::loadParams();
}

uking::dmg::DamageCallback* SetIgnoreDrownDCCallBack::m14() {
    return &_30;
}

}  // namespace uking::behavior
