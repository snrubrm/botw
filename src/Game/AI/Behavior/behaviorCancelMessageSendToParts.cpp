#include "Game/AI/Behavior/behaviorCancelMessageSendToParts.h"

namespace uking::behavior {

CancelMessageSendToParts::CancelMessageSendToParts(const InitArg& arg)
    : CancelMessageSendToPartsBase(arg) {}

CancelMessageSendToParts::~CancelMessageSendToParts() = default;

bool CancelMessageSendToParts::m6(sead::Heap* heap) {
    return CancelMessageSendToPartsBase::m6(heap);
}

void CancelMessageSendToParts::m7() {
    CancelMessageSendToPartsBase::m7();
}

void CancelMessageSendToParts::m8() {
    CancelMessageSendToPartsBase::m8();
}

void CancelMessageSendToParts::m9() {
    CancelMessageSendToPartsBase::m9();
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
