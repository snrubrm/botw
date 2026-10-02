#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// CSV name. Vtable 0x710250bd00 (no RTTI). Static state descriptors are global objects whose names
// are strings like "::StateID_Active"; subclasses forward enter/run/leave to member function pointers.
class StateBase {
public:
    constexpr StateBase(s32 id, const char* name) : mId(id), mName(name) {}
    virtual ~StateBase();
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
    Unk1* _0;
    const StateBase* mNextState = nullptr;
    Unk2* mCurrent = nullptr;
    const StateBase* mPrevState = &sUnk_710250bcd8;
    Unk2* mPrevious = nullptr;
};
KSYS_CHECK_SIZE_NX150(StateMachine, 0x28);

}  // namespace ksys
