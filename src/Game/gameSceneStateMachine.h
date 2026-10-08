#pragma once

#include "KingSystem/Utils/StateMachine.h"

namespace uking {

// Binds a ksys::StateBase to its owner and counts the frames it runs (the implementation of
// StateMachine::Unk2 in the GameScene TU; CSV StateMachineWrapper__, 0x71007b705c-0x71007b7138; name is a guess).
class StateMachineOwnerBinding : public ksys::StateMachine::Unk2 {
public:
    ~StateMachineOwnerBinding() override;
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

// Hands out the embedded binding for a state (CSV GameScene::StateMachineWrapper_, 0x71007b7044; name is a guess).
class StateMachineOwnerBindingHolder : public ksys::StateMachine::Unk1 {
public:
    // (the first out-of-line virtual)
    ksys::StateMachine::Unk2* setState(const ksys::StateBase* state) override;
    void m3(ksys::StateMachine::Unk2** wrapper) override { *wrapper = nullptr; }

    /* 0x08 */ StateMachineOwnerBinding mBinding;
};

// A state machine owner with its own Unk1 holder (CSV StateMachineWrapper, vtable 0x710245a820; the StateMachine at
// +0x30 uses the Holder at +8). Method names are the CSV names.
class StateMachineWrapper {
public:
    virtual ~StateMachineWrapper();
    // Enters the pending state (if any).
    virtual void replaceState();
    // Enters the pending state without checking that there is one.
    virtual void changeStateFast();
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

    /* 0x08 */ StateMachineOwnerBindingHolder mHolder;
    /* 0x30 */ ksys::StateMachine mMachine;
};

}  // namespace uking
