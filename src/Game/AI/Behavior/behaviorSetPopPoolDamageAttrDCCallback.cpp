#include "Game/AI/Behavior/behaviorSetPopPoolDamageAttrDCCallback.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling (params at 0x30 stored after 0x50)
SetPopPoolDamageAttrDCCallback::SetPopPoolDamageAttrDCCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetPopPoolDamageAttrDCCallback::~SetPopPoolDamageAttrDCCallback() = default;

bool SetPopPoolDamageAttrDCCallback::m6(sead::Heap* heap) {
    return SetDamageCallback::m6(heap);
}

void SetPopPoolDamageAttrDCCallback::m7() {
    SetDamageCallback::m7();
}

void SetPopPoolDamageAttrDCCallback::m8() {
    switch (*mAttrForSmall_s) {
    case -1:
        _40._24 = -1;
        break;
    case 0:
        _40._24 = 1;
        break;
    case 1:
        _40._24 = 2;
        break;
    case 2:
        _40._24 = 5;
        break;
    case 3:
        _40._24 = 17;
        break;
    case 4:
        _40._24 = 21;
        break;
    case 5:
        _40._24 = 22;
        break;
    default:
        _40._24 = -1;
        break;
    }
    switch (*mAttrForFinish_s) {
    case -1:
        _40._28 = -1;
        break;
    case 0:
        _40._28 = 1;
        break;
    case 1:
        _40._28 = 2;
        break;
    case 2:
        _40._28 = 5;
        break;
    case 3:
        _40._28 = 17;
        break;
    case 4:
        _40._28 = 21;
        break;
    case 5:
        _40._28 = 22;
        break;
    default:
        _40._28 = -1;
        break;
    }
    SetDamageCallback::m8();
}

void SetPopPoolDamageAttrDCCallback::m9() {
    SetDamageCallback::m9();
}

void SetPopPoolDamageAttrDCCallback::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mAttrForSmall_s, "AttrForSmall");
    getStaticParam(&mAttrForFinish_s, "AttrForFinish");
}

uking::dmg::DamageCallback* SetPopPoolDamageAttrDCCallback::m14() {
    return &_40;
}

}  // namespace uking::behavior
