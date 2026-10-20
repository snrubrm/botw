#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys {

class Message;
class MessageTransceiverBase;
class MessageQueue;
struct MesTransceiverId;

class IMessageBrokerRegister {
public:
    struct IForEachContext {
        virtual ~IForEachContext() = default;
        virtual void process(const MesTransceiverId& id) = 0;
    };

    virtual ~IMessageBrokerRegister() = default;
    virtual bool registerTransceiver(const MesTransceiverId& id) = 0;
    virtual void deregisterTransceiver(const MesTransceiverId& id) = 0;
    virtual void forEachRegistered(IForEachContext& context) = 0;
    virtual void setId(const u32& id) = 0;
    virtual const u32& getId() const = 0;
    virtual int countTransceivers() const = 0;
};

// Placeholder base of the message argument classes (typeinfo 0x71025d0530; the original has no
// vtable for it). Also the base of the placeholder classes Unk_710246c410 / Unk_710250b7c0.
class Unk_71025d0530 {
    SEAD_RTTI_BASE(Unk_71025d0530)
public:
    virtual ~Unk_71025d0530() = default;
};

class IMessageBroker {
public:
    class SetIdArg : public Unk_71025d0530 {
        SEAD_RTTI_OVERRIDE(SetIdArg, Unk_71025d0530)
    public:
        SetIdArg() = default;
        explicit SetIdArg(u32 id) { setId(id); }
        virtual ~SetIdArg() = default;
        u32 getId() const { return mId; }
        void setId(u32 id) { mId = id; }

    private:
        u32 mId{};
    };

    IMessageBroker();
    virtual ~IMessageBroker();
    // DebugBoard broker 89B6B0 accepts null and reports whether the RTTI argument
    // was accepted; it reads the ID at 8 and stores it in the owned register.
    virtual bool setId(const SetIdArg* arg) = 0;
    virtual IMessageBrokerRegister* getRegister() = 0;
    bool registerTransceiver(const MessageTransceiverBase& transceiver);
    void deregisterTransceiver(const MessageTransceiverBase& transceiver);
    int countTransceivers();
};

}  // namespace ksys
