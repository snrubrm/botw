#pragma once

#include "Game/UI/uiStateMachineWrapper.h"
#include "KingSystem/Utils/Thread/MessageReceiver.h"
#include "KingSystem/Utils/Thread/MessageReceiverAdapter.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace uking::ui {

// ScreenChild constructs this state wrapper at +0x50 (vtable 0x71025098d0; Screen: 0x710250a258); its receiver base is at +0xa8.
template <typename Owner>
class Unk_71025098d0 : public Unk_7102474a70<Owner>, public ksys::MessageReceiver {
public:
    using Unk_7102474a70<Owner>::mMachine;

    ~Unk_71025098d0() override = default;
    void run() override { mMachine.run(); }
    // NON_MATCHING: the bool state callback result requires conversion to the receiver's int result.
    int receive(const ksys::Message& message) override {
        if (!mMachine.mCurrent)
            Unk_7102474a70<Owner>::replaceState();
        if (mMachine.mCurrent && mMachine.mCurrent->reenter(const_cast<ksys::Message*>(&message)))
            return 1;
        if (mMachine.mCurrent)
            return mMachine.mCurrent->exec5(const_cast<ksys::Message*>(&message));
        return 0;
    }
    void receive(const ksys::MessageAck& ack) override {
        if (mMachine.mCurrent)
            mMachine.mCurrent->exec6(const_cast<ksys::MessageAck*>(&ack));
    }
};

// ScreenChild constructs this transceiver at +0x38 (vtable 0x7102474a28; Screen: +0x118, 0x710250a210) and registers its receiver adapter.
template <typename Owner>
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

    /* 0x18 */ Unk_71025098d0<Owner> mReceiver;
    /* 0x90 */ ksys::MessageReceiverAdapter mAdapter;
};

template <typename Owner>
bool Unk_7102474a28<Owner>::sendMessage(const ksys::MesTransceiverId& dest,
                                const ksys::MessageType& type, void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(), dest,
                                                   type, user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

template <typename Owner>
bool Unk_7102474a28<Owner>::sendMessageOnProcessingThread(const ksys::MesTransceiverId& dest,
                                                  const ksys::MessageType& type,
                                                  void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), dest, type, user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

template <typename Owner>
bool Unk_7102474a28<Owner>::sendMessage(ksys::IMessageBroker& broker,
                                const ksys::MessageType& type, void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(),
                                                   *getRegister(broker), type, user_data, ack, false);
    if (sent) {
        int count = broker.countTransceivers();
        if (count > 0) {
            do {
                mAdapter.setFlag(ack);
            } while (--count);
        }
    }
    return sent;
}

template <typename Owner>
bool Unk_7102474a28<Owner>::sendMessageOnProcessingThread(ksys::IMessageBroker& broker,
                                                  const ksys::MessageType& type,
                                                  void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), *getRegister(broker), type, user_data, ack, false);
    if (sent) {
        int count = broker.countTransceivers();
        if (count > 0) {
            do {
                mAdapter.setFlag(ack);
            } while (--count);
        }
    }
    return sent;
}

template <typename Owner>
ksys::MessageReceiverEx* Unk_7102474a28<Owner>::getReceiver() {
    return &mAdapter;
}



}  // namespace uking::ui
