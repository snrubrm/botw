#pragma once

#include "KingSystem/Utils/Thread/MessageReceiverEx.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace ksys {

class Message;

class MessageTransceiverTxOnly final : public MessageTransceiverBase {
public:
    class IHandler {
    public:
        virtual ~IHandler() = default;
        // Not pure: AmiiboMgr and IceBlockMgr (which only override handleMessage) both point their
        // second vtable's slot at the same empty function (0x710064c188).
        virtual void handleAck(const MessageAck& ack) {}
    };

    // Takes a pointer: owners pass their actor (`mActor`, whose IHandler base is at +0x188) with a
    // null check (RemainsElectricWeakPointWait, TowingPlayer, PlayerStainWait, ... ctors).
    explicit MessageTransceiverTxOnly(IHandler* handler);
    ~MessageTransceiverTxOnly() override;
    bool sendMessage(const MesTransceiverId& dest, const MessageType& type, void* user_data,
                     bool ack) override;
    bool sendMessageOnProcessingThread(const MesTransceiverId& dest, const MessageType& type,
                                       void* user_data, bool ack) override;
    bool sendMessage(IMessageBroker& broker, const MessageType& type, void* user_data,
                     bool ack) override;
    bool sendMessageOnProcessingThread(IMessageBroker& broker, const MessageType& type,
                                       void* user_data, bool ack) override;
    MessageReceiverEx* getReceiver() override;

private:
    class Receiver : public MessageReceiverEx {
        SEAD_RTTI_OVERRIDE(Receiver, MessageReceiverEx)
    public:
        explicit Receiver(IHandler* handler) : mHandler(handler) {}
        ~Receiver() override;
        void handleAck(const MessageAck& ack) override;

    private:
        IHandler* mHandler;
    };

    Receiver mReceiver;
};

}  // namespace ksys
