#include "KingSystem/System/DebugBoard.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

// 0x710089c5ac / 0x710089c5c0 (D1) / 0x710089c614 (D0)
Unk_710246c458::Unk_710246c458() : mTransceiver(nullptr) {}

Unk_710246c458::~Unk_710246c458() {
    if (mTransceiver)
        DebugBoardMgr::instance()->getBroker0()->deregisterTransceiver(*mTransceiver);
}

bool Unk_710246c458::sub_710089C664(const DebugBoardTransceiverArgMaybe& arg) {
    if (!arg.mTransceiver)
        return false;
    mTransceiver = arg.mTransceiver;
    DebugBoardMgr::instance()->getBroker0()->registerTransceiver(*arg.mTransceiver);
    return true;
}

// 0x710089c7d4 / 0x710089c7e8 (D1) / 0x710089c83c (D0)
Unk_710246c498::Unk_710246c498() : mTransceiver(nullptr) {}

Unk_710246c498::~Unk_710246c498() {
    if (mTransceiver)
        DebugBoardMgr::instance()->getBroker1()->deregisterTransceiver(*mTransceiver);
}

bool Unk_710246c498::sub_710089C88C(const DebugBoardTransceiverArgMaybe& arg) {
    if (!arg.mTransceiver)
        return false;
    mTransceiver = arg.mTransceiver;
    DebugBoardMgr::instance()->getBroker1()->registerTransceiver(*arg.mTransceiver);
    return true;
}

// 0x710089c94c / 0x710089c960 (D1) / 0x710089c9b4 (D0)
Unk_710246c4d8::Unk_710246c4d8() : mTransceiver(nullptr) {}

Unk_710246c4d8::~Unk_710246c4d8() {
    if (mTransceiver)
        DebugBoardMgr::instance()->getBroker2()->deregisterTransceiver(*mTransceiver);
}

bool Unk_710246c4d8::sub_710089CA04(const DebugBoardTransceiverArgMaybe& arg) {
    if (!arg.mTransceiver)
        return false;
    mTransceiver = arg.mTransceiver;
    DebugBoardMgr::instance()->getBroker2()->registerTransceiver(*arg.mTransceiver);
    return true;
}

void DebugBoardMgr::sub_710089BA4C(bool on) {
    _44c0 = on ? _44c0 | 0x20000 : _44c0 & ~0x20000u;
}

// NON_MATCHING: the original merges the constant stores into 64-bit pairs and shares the last two stores of
// both branches (indexed by 15 / 16 or 1 / 7).
void DebugBoardMgr::sub_710089BA6C(bool on) {
    if (_44b0 == on)
        return;

    if (on) {
        _4530[0] = 2;
        _4530[1] = 2;
        _4530[2] = 2;
        _4530[3] = 2;
        _4530[4] = 2;
        _4530[5] = 2;
        _4530[6] = 2;
        _4530[7] = 2;
        _4530[8] = 2;
        _4530[9] = 2;
        _4530[10] = 2;
        _4530[11] = 2;
        _4530[12] = 2;
        _4530[13] = 2;
        _4530[15] = 2;
        _4530[16] = 2;
    } else {
        _4530[1] = 1;
        _4530[7] = 1;
    }
    _44b0 = on;
}

ksys::MesTransceiverId sDebugBoardMessageTarget;

Unk_710246c478::Unk_710246c478() = default;
Unk_710246c478::~Unk_710246c478() = default;

bool Unk_710246c478::sub_710089C6FC(ksys::MessageTransceiverBase* transceiver,
                                     const ksys::MessageType* type, void* target, bool ack) {
    if (!transceiver)
        return false;
    return transceiver->sendMessage(sDebugBoardMessageTarget, ksys::MessageType(*type), target, ack);
}

bool Unk_710246c478::sub_710089C754(ksys::MessageTransceiverBase* transceiver,
                                     const ksys::MessageType* type, void* target, bool ack) {
    if (!transceiver)
        return false;
    return transceiver->sendMessageOnProcessingThread(sDebugBoardMessageTarget, ksys::MessageType(*type), target, ack);
}
