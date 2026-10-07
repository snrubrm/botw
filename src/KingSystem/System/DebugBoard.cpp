#include "KingSystem/System/DebugBoard.h"

// 0x710089c5ac / 0x710089c5c0 (D1) / 0x710089c614 (D0)
Unk_710246c458::Unk_710246c458() : mTransceiver(nullptr) {}

Unk_710246c458::~Unk_710246c458() {
    if (mTransceiver)
        DebugBoardMgr::instance()->getBroker0()->deregisterTransceiver(*mTransceiver);
}

// 0x710089c7d4 / 0x710089c7e8 (D1) / 0x710089c83c (D0)
Unk_710246c498::Unk_710246c498() : mTransceiver(nullptr) {}

Unk_710246c498::~Unk_710246c498() {
    if (mTransceiver)
        DebugBoardMgr::instance()->getBroker1()->deregisterTransceiver(*mTransceiver);
}

// 0x710089c94c / 0x710089c960 (D1) / 0x710089c9b4 (D0)
Unk_710246c4d8::Unk_710246c4d8() : mTransceiver(nullptr) {}

Unk_710246c4d8::~Unk_710246c4d8() {
    if (mTransceiver)
        DebugBoardMgr::instance()->getBroker2()->deregisterTransceiver(*mTransceiver);
}
