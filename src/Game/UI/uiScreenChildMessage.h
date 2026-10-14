#pragma once

#include "Game/UI/uiStateMachineWrapper.h"
#include "KingSystem/Utils/Thread/MessageReceiver.h"
#include "KingSystem/Utils/Thread/MessageReceiverAdapter.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace uking::ui {

// ScreenChild constructs this state wrapper at +0x50; its receiver base is at +0xa8.
class Unk_71025098d0 : public Unk_7102474a70, public ksys::MessageReceiver {
public:
    ~Unk_71025098d0() override = default;
    void run() override;
    int receive(const ksys::Message& message) override;
    void receive(const ksys::MessageAck& ack) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71025098d0, 0x78);

// ScreenChild constructs this transceiver at +0x38 and registers its receiver adapter.
class Unk_7102474a28 : public ksys::MessageTransceiverBase {
public:
    // NON_MATCHING: the original takes the adapter address after the getDispatcher call.
    // Inline: ScreenChild subclass destructors in other TUs inline this teardown.
    ~Unk_7102474a28() override { deregisterReceiver(mAdapter); }
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

    /* 0x18 */ Unk_71025098d0 mReceiver;
    /* 0x90 */ ksys::MessageReceiverAdapter mAdapter;
};
KSYS_CHECK_SIZE_NX150(Unk_7102474a28, 0xc8);

}  // namespace uking::ui
