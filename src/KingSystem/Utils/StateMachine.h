#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace uking {
class StateMachineWrapper;
}

namespace ksys {

// CSV name. Vtable 0x710250bd00 (no RTTI). Static state descriptors are global objects whose names
// are strings like "::StateID_Active"; subclasses forward enter/run/leave to member function pointers.
class StateBase {
public:
    constexpr StateBase(s32 id, const char* name) : mId(id), mName(name) {}
    virtual ~StateBase() = default;
    virtual s32 getId() const;
    virtual const char* getName() const;
    virtual void enter(void* owner) const;
    virtual void run(void* owner) const;
    virtual void leave(void* owner) const;
    virtual bool exec4(void* owner, void* arg) const;
    virtual bool return0(void* owner, void* arg) const;
    virtual void null(void* owner, void* arg) const;

    s32 mId;
    const char* mName;
};
KSYS_CHECK_SIZE_NX150(StateBase, 0x18);

// A state whose enter / run / leave / exec4 callbacks are virtual member functions of the owner class T
// (instantiated once per owner; the owners keep their static state objects in a TU-local initialiser).
// The layout (vtable, id, name, four 16-byte member function pointers at 0x18 / 0x28 / 0x38 / 0x48, a
// pointer to a parent state at 0x58; size 0x60) and the ten overridden virtual slots come from the
// instantiations of the UI screens (e.g. ScreenRupee).
template <typename T>
class StateTemplate : public StateBase {
public:
    using Callback = void (T::*)();
    using Callback4 = bool (T::*)(void*);

    constexpr StateTemplate(s32 id, const char* name, Callback enter, Callback run, Callback leave,
                            Callback4 exec4, const StateBase* parent)
        : StateBase(id, name), mEnter(enter), mRun(run), mLeave(leave), mExec4(exec4),
          mParent(parent) {}

    s32 getId() const override {
        if (mParent->mId != -1)
            return mParent->getId();
        return mId;
    }
    void enter(void* owner) const override { (static_cast<T*>(owner)->*mEnter)(); }
    void run(void* owner) const override { (static_cast<T*>(owner)->*mRun)(); }
    void leave(void* owner) const override { (static_cast<T*>(owner)->*mLeave)(); }
    bool exec4(void* owner, void* arg) const override { return (static_cast<T*>(owner)->*mExec4)(arg); }
    bool return0(void*, void*) const override { return false; }
    void null(void*, void*) const override {}

    Callback mEnter;
    Callback mRun;
    Callback mLeave;
    Callback4 mExec4;
    const StateBase* mParent;
};

// 0x710250bcd8 (id -1, no name): the state returned by StateMachine::getState when there is none.
extern StateBase sUnk_710250bcd8;

// CSV name.
class StateMachine {
public:
    // Binds a StateBase to its owner (implementations: CSV StateMachineWrapper__, D1 0x7b705c); enter/run/
    // leave forward to the StateBase with the owner as argument.
    class Unk2 {
    public:
        virtual ~Unk2() = default;
        virtual const StateBase& getState() const = 0;
        virtual void enter() = 0;
        virtual void run() = 0;
        virtual void leave() = 0;
        virtual s32 getRunCount() const = 0;
        // The state's exec4 / return0 / null with the bound owner (the implementation at 0x7b70f4 / 0x7b710c / 0x7b7124).
        virtual bool reenter(void* arg) = 0;
        virtual bool exec5(void* arg) = 0;
        virtual void exec6(void* arg) = 0;
    };

    // Hands out the Unk2 for a state (owners embed an implementation holding one Unk2, CSV
    // StateMachineWrapper_) and takes it back.
    class Unk1 {
    public:
        virtual ~Unk1() = default;
        virtual Unk2* setState(const StateBase* state) = 0;
        virtual void m3(Unk2** wrapper) = 0;
    };

    StateMachine(Unk1* unk, const StateBase& state);

    const StateBase* getState() const;
    void run();
    void sub_71010BFE64();
    void changeState(const StateBase* state);

private:
    friend class ::uking::StateMachineWrapper;

    Unk1* _0;
    const StateBase* mNextState = nullptr;
    Unk2* mCurrent = nullptr;
    const StateBase* mPrevState = &sUnk_710250bcd8;
    Unk2* mPrevious = nullptr;
};
KSYS_CHECK_SIZE_NX150(StateMachine, 0x28);

}  // namespace ksys
