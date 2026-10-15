#pragma once

#include "Game/gameSceneStateMachine.h"
#include "KingSystem/Utils/Thread/MessageReceiver.h"
#include "KingSystem/Utils/Thread/MessageReceiverAdapter.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace uking {

// Intermediate table installed at GameScene +0x1a0 before its receiver base is constructed.
// All fourteen primary slots are inherited from StateMachineWrapper.
class Unk_710245a7a0 : public StateMachineWrapper {
public:
    using StateMachineWrapper::StateMachineWrapper;
    ~Unk_710245a7a0() override;
};
KSYS_CHECK_SIZE_NX150(Unk_710245a7a0, 0x58);

// Primary table 245A6D0; secondary MessageReceiver table 245A760 has offset-to-top -0x58.
class Unk_710245a6d0 : public Unk_710245a7a0, public ksys::MessageReceiver {
public:
    using Unk_710245a7a0::Unk_710245a7a0;
    ~Unk_710245a6d0() override;
    void run() override;
    int receive(const ksys::Message& message) override;
    void receive(const ksys::MessageAck& ack) override;
};
KSYS_CHECK_SIZE_NX150(Unk_710245a6d0, 0x78);

// GameScene constructs this complete transceiver at +0x188 and registers its adapter at +0x218.
class Unk_710245a688 : public ksys::MessageTransceiverBase {
public:
    Unk_710245a688(void* owner, const ksys::StateBase& state)
        : mReceiver(owner, state), mAdapter(&mReceiver) {
        registerReceiver(mAdapter);
    }
    ~Unk_710245a688() override;
    bool sendMessage(const ksys::MesTransceiverId& dest, const ksys::MessageType& type,
                     void* user_data, bool ack) override;
    bool sendMessageOnProcessingThread(const ksys::MesTransceiverId& dest,
                                       const ksys::MessageType& type, void* user_data,
                                       bool ack) override;
    bool sendMessage(ksys::IMessageBroker& broker, const ksys::MessageType& type,
                     void* user_data, bool ack) override;
    bool sendMessageOnProcessingThread(ksys::IMessageBroker& broker,
                                       const ksys::MessageType& type, void* user_data,
                                       bool ack) override;
    ksys::MessageReceiverEx* getReceiver() override;

    /* 0x18 */ Unk_710245a6d0 mReceiver;
    /* 0x90 */ ksys::MessageReceiverAdapter mAdapter;
};
KSYS_CHECK_SIZE_NX150(Unk_710245a688, 0xc8);

}  // namespace uking
