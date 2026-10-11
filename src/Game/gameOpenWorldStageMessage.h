#pragma once

#include "KingSystem/Utils/StateMachine.h"
#include "KingSystem/Utils/Thread/MessageReceiver.h"
#include "KingSystem/Utils/Thread/MessageReceiverAdapter.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace uking {

class OpenWorldStage;

// State descriptor table 0x710245b478. Its last two operations dispatch to the owner.
class Unk_710245b478 : public ksys::StateTemplate<OpenWorldStage> {
public:
    using StateTemplate::StateTemplate;
    bool return0(void* owner, void* arg) const override;
    void null(void* owner, void* arg) const override;
};
KSYS_CHECK_SIZE_NX150(Unk_710245b478, 0x60);

// OpenWorldStage binding at +0x38, established by constructor 7C428C and table 245B740.
class Unk_710245b740 : public ksys::StateMachine::Unk2 {
public:
    explicit Unk_710245b740(void* owner) : mOwner(owner), mState(nullptr), mRunCount(0) {}
    ~Unk_710245b740() override = default;
    // (the first out-of-line virtual: the vtable is emitted with it)
    const ksys::StateBase& getState() const override;
    void enter() override;
    void run() override;
    void leave() override;
    s32 getRunCount() const override { return mRunCount; }
    bool reenter(void* arg) override { return mState->exec4(mOwner, arg); }
    bool exec5(void* arg) override { return mState->return0(mOwner, arg); }
    void exec6(void* arg) override { mState->null(mOwner, arg); }

    /* 0x08 */ void* mOwner;
    /* 0x10 */ const ksys::StateBase* mState;
    /* 0x18 */ s32 mRunCount;
};

// Holder at OpenWorldStage +0x30; table 245B710.
class Unk_710245b710 : public ksys::StateMachine::Unk1 {
public:
    explicit Unk_710245b710(void* owner) : mBinding(owner) {}
    ~Unk_710245b710() override;
    ksys::StateMachine::Unk2* setState(const ksys::StateBase* state) override;
    void m3(ksys::StateMachine::Unk2** wrapper) override { *wrapper = nullptr; }

    /* 0x08 */ Unk_710245b740 mBinding;
};

// Complete fourteen-slot wrapper at OpenWorldStage +0x28; table 245B690.
class Unk_710245b690 {
public:
    Unk_710245b690(void* owner, const ksys::StateBase& state)
        : mHolder(owner), mMachine(&mHolder, state) {}
    // The native base destructor follows the slot methods and is inlined into receiver lifetimes.
    // NON_MATCHING: the final cleanup argument is scheduled before the frame restore.
    virtual ~Unk_710245b690() {
        mMachine._0->m3(&mMachine.mPrevious);
        mMachine._0->m3(&mMachine.mCurrent);
    }
    // Enters the pending state (if any).
    virtual void replaceState();
    // Enters the supplied state immediately.
    virtual void changeStateFast(const ksys::StateBase* state);
    virtual void run();
    virtual void leaveState();
    virtual void enterState();
    virtual void changeState(const ksys::StateBase* state);
    virtual const ksys::StateBase* getState() const;
    virtual const ksys::StateBase* getSubstate() const;
    virtual s32 getRunCount() const;
    virtual bool reenter(void* arg);
    virtual bool exec5(void* arg);
    virtual void exec6(void* arg);

    /* 0x08 */ Unk_710245b710 mHolder;
    /* 0x30 */ ksys::StateMachine mMachine;
};

// Intermediate table installed at OpenWorldStage +0x28 before its receiver base is constructed.
// All fourteen primary slots are inherited from Unk_710245b690.
class Unk_710245b610 : public Unk_710245b690 {
public:
    using Unk_710245b690::Unk_710245b690;
    ~Unk_710245b610() override = default;
};
KSYS_CHECK_SIZE_NX150(Unk_710245b610, 0x58);

// Primary table 245B540; secondary MessageReceiver table 245B5D0 has offset-to-top -0x58.
class Unk_710245b540 : public Unk_710245b610, public ksys::MessageReceiver {
public:
    using Unk_710245b610::Unk_710245b610;
    ~Unk_710245b540() override;
    void run() override;
    int receive(const ksys::Message& message) override;
    void receive(const ksys::MessageAck& ack) override;
};
KSYS_CHECK_SIZE_NX150(Unk_710245b540, 0x78);

// OpenWorldStage constructs this complete transceiver at +0x10 and registers its adapter at +0xa0.
class Unk_710245b4f8 : public ksys::MessageTransceiverBase {
public:
    Unk_710245b4f8(void* owner, const ksys::StateBase& state)
        : mReceiver(owner, state), mAdapter(&mReceiver) {
        registerReceiver(mAdapter);
    }
    ~Unk_710245b4f8() override;
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

    /* 0x18 */ Unk_710245b540 mReceiver;
    /* 0x90 */ ksys::MessageReceiverAdapter mAdapter;
};
KSYS_CHECK_SIZE_NX150(Unk_710245b4f8, 0xc8);

}  // namespace uking
