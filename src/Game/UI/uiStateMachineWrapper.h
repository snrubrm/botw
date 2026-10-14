#pragma once

#include "KingSystem/Utils/StateMachine.h"

namespace uking::ui {

// Binds a StateBase to the owner and counts the frames it has run (ksys::StateMachine::Unk2 implementation;
// vtables 0x7102509a50 (ScreenChild) / 0x710250a458 (Screen)). The GameScene TU has the same code as the
// non-template uking::StateMachineOwnerBinding; the names here are guesses modelled on it.
// The destructor slot is the shared empty base destructor at 0x71007b705c (the implicit destructor aliases it).
template <typename Owner>
class StateOwnerBinding : public ksys::StateMachine::Unk2 {
public:
    explicit StateOwnerBinding(Owner* owner) : mOwner(owner), mState(nullptr), mRunCount(0) {}
    const ksys::StateBase& getState() const override { return *mState; }
    void enter() override {
        mRunCount = 0;
        mState->enter(mOwner);
    }
    void run() override {
        mState->run(mOwner);
        ++mRunCount;
    }
    void leave() override {
        mState->leave(mOwner);
        mState = nullptr;
        mRunCount = 0;
    }
    s32 getRunCount() const override { return mRunCount; }
    bool reenter(void* arg) override { return mState->exec4(mOwner, arg); }
    bool exec5(void* arg) override { return mState->return0(mOwner, arg); }
    void exec6(void* arg) override { mState->null(mOwner, arg); }

    /* 0x08 */ Owner* mOwner;
    /* 0x10 */ const ksys::StateBase* mState;
    /* 0x18 */ s32 mRunCount;
};

// Hands out the embedded binding (ksys::StateMachine::Unk1 implementation; vtables 0x7102509a20 (ScreenChild) /
// 0x710250a428 (Screen)). Same code as the GameScene TU's uking::StateMachineOwnerBindingHolder.
template <typename Owner>
class StateOwnerBindingHolder : public ksys::StateMachine::Unk1 {
public:
    explicit StateOwnerBindingHolder(Owner* owner) : mBinding(owner) {}
    ksys::StateMachine::Unk2* setState(const ksys::StateBase* state) override {
        mBinding.mState = state;
        return &mBinding;
    }
    void m3(ksys::StateMachine::Unk2** wrapper) override { *wrapper = nullptr; }

    /* 0x08 */ StateOwnerBinding<Owner> mBinding;
};

// UI state-machine wrapper, vtable 0x7102474a70 (ScreenChild) / 0x710250a3a8 (Screen). Its holder at +8
// remains opaque; the original virtual methods access StateMachine at +0x30.
// A template over the owner: the Screen TU has its own copy of every method (0x71010ad0e4..) with
// its own vtables, while the ScreenChild copy lives at 0x71009327fc.
template <typename Owner>
class Unk_7102474a70 {
public:
    Unk_7102474a70(Owner* owner, const ksys::StateBase& state) : mHolder(owner), mMachine(&mHolder, state) {}
    // NON_MATCHING: the original schedules its final argument after the virtual load.
    // Inline: ScreenChild subclass destructors in other TUs inline this teardown.
    virtual ~Unk_7102474a70() {
        mMachine._0->m3(&mMachine.mPrevious);
        mMachine._0->m3(&mMachine.mCurrent);
    }
    // The native receiver message path also inlines this state transition.
    virtual void replaceState() {
        if (mMachine.mNextState) {
            mMachine.mCurrent = mMachine._0->setState(mMachine.mNextState);
            mMachine.mCurrent->enter();
            mMachine.mNextState = nullptr;
        }
    }
    virtual void changeStateFast(const ksys::StateBase* state) {
        mMachine.mCurrent = mMachine._0->setState(state);
        mMachine.mCurrent->enter();
    }
    virtual void run() { mMachine.run(); }
    virtual void leaveState() { mMachine.sub_71010BFE64(); }
    virtual void enterState() { mMachine.mCurrent->enter(); }
    virtual void changeState(const ksys::StateBase* state) { mMachine.changeState(state); }
    virtual const ksys::StateBase* getState() const { return mMachine.getState(); }
    virtual const ksys::StateBase* getSubstate() const { return mMachine.mPrevState; }
    virtual s32 getRunCount() const { return mMachine.mCurrent->getRunCount(); }
    virtual bool reenter(void* arg) {
        if (!mMachine.mCurrent)
            Unk_7102474a70::replaceState();
        if (mMachine.mCurrent)
            return mMachine.mCurrent->reenter(arg);
        return false;
    }
    virtual bool exec5(void* arg) {
        if (mMachine.mCurrent)
            return mMachine.mCurrent->exec5(arg);
        return false;
    }
    virtual void exec6(void* arg) {
        if (mMachine.mCurrent)
            mMachine.mCurrent->exec6(arg);
    }
public:
    /* 0x08 */ StateOwnerBindingHolder<Owner> mHolder;
    /* 0x30 */ ksys::StateMachine mMachine;
};

// Intermediate class with no own slots (vtable 0x71025099a0 (ScreenChild) / 0x710250a328 (Screen); only D0 is its own),
// like the GameScene TU's Unk_710245a7a0.
template <typename Owner>
class Unk_71025099a0 : public Unk_7102474a70<Owner> {
public:
    using Unk_7102474a70<Owner>::Unk_7102474a70;
    ~Unk_71025099a0() override = default;
};


}  // namespace uking::ui
