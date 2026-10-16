#include "Game/Actor/Behavior/behaviorSetPopPoolDamageAttrDCCallback.h"

namespace uking::behavior {

SetPopPoolDamageAttrDCCallback::SetPopPoolDamageAttrDCCallback(const InitArg& arg)
    : SetDamageCallback(arg) {}

SetPopPoolDamageAttrDCCallback::~SetPopPoolDamageAttrDCCallback() = default;

bool SetPopPoolDamageAttrDCCallback::init_(sead::Heap* heap) {
    return SetDamageCallback::init_(heap);
}

void SetPopPoolDamageAttrDCCallback::calc() {
    SetDamageCallback::calc();
}

void SetPopPoolDamageAttrDCCallback::enter() {
    switch (*mParams.mAttrForSmall_s) {
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
    switch (*mParams.mAttrForFinish_s) {
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
    SetDamageCallback::enter();
}

void SetPopPoolDamageAttrDCCallback::leave() {
    SetDamageCallback::leave();
}

void SetPopPoolDamageAttrDCCallback::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mParams.mAttrForSmall_s, "AttrForSmall");
    getStaticParam(&mParams.mAttrForFinish_s, "AttrForFinish");
}

uking::act::DamageCallback* SetPopPoolDamageAttrDCCallback::m14() {
    return &_40;
}

}  // namespace uking::behavior
