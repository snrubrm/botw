#include "KingSystem/System/DebugBoard.h"

DebugBoardMgr* DebugBoardMgr::sInstance;

// 0x710089baf4
ksys::IMessageBroker* DebugBoardMgr::getBroker0() {
    return &mBroker0;
}

// 0x710089bafc
ksys::IMessageBroker* DebugBoardMgr::getBroker1() {
    return &mBroker1;
}

// 0x710089bb08
ksys::IMessageBroker* DebugBoardMgr::getBroker2() {
    return &mBroker2;
}

Unk_DebugBoardRegister::~Unk_DebugBoardRegister() = default;

bool Unk_DebugBoardRegister::registerTransceiver(const ksys::MesTransceiverId& id) {
    if (!id.isRegistered())
        return false;
    for (u32 i = 0; i < 200; ++i) {
        auto& entry = mIds[i];
        if (!entry.isRegistered()) {
            entry = id;
            return true;
        }
    }
    return false;
}

void Unk_DebugBoardRegister::deregisterTransceiver(const ksys::MesTransceiverId& id) {
    if (!id.isRegistered())
        return;
    for (int i = 0; i < 200; ++i) {
        auto& entry = mIds[i];
        if (entry.isRegistered() && entry.queue_id == id.queue_id && entry.id == id.id)
            entry.reset();
    }
}

void Unk_DebugBoardRegister::forEachRegistered(IForEachContext& context) {
    for (int i = 0; i < 200; ++i) {
        auto& entry = mIds[i];
        if (entry.isRegistered())
            context.process(entry);
        else
            entry.reset();
    }
}

void Unk_DebugBoardRegister::setId(const u32& id) {
    mId = id;
}

const u32& Unk_DebugBoardRegister::getId() const {
    return mId;
}

int Unk_DebugBoardRegister::countTransceivers() const {
    int count = 0;
    for (const auto& entry : mIds) {
        if (entry.isRegistered())
            ++count;
    }
    return count;
}

Unk_DebugBoardBroker::~Unk_DebugBoardBroker() = default;

ksys::IMessageBrokerRegister* Unk_DebugBoardBroker::getRegister() {
    return &mRegister;
}
