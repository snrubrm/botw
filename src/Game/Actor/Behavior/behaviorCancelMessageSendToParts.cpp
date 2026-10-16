#include "Game/Actor/Behavior/behaviorCancelMessageSendToParts.h"

namespace uking::behavior {

CancelMessageSendToParts::CancelMessageSendToParts(const InitArg& arg)
    : CancelMessageSendToPartsBase(arg) {}

CancelMessageSendToParts::~CancelMessageSendToParts() = default;

bool CancelMessageSendToParts::init_(sead::Heap* heap) {
    return CancelMessageSendToPartsBase::init_(heap);
}

void CancelMessageSendToParts::calc() {
    CancelMessageSendToPartsBase::calc();
}

void CancelMessageSendToParts::enter() {
    CancelMessageSendToPartsBase::enter();
}

void CancelMessageSendToParts::leave() {
    CancelMessageSendToPartsBase::leave();
}

void CancelMessageSendToParts::loadParams() {
    CancelMessageSendToPartsBase::loadParams();
}

void CancelMessageSendToParts::m14() {
    _50.x(mActor);
}

Unk_7102357d20* CancelMessageSendToParts::m15() {
    return &_50;
}

}  // namespace uking::behavior
