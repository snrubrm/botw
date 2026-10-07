#pragma once

#include "KingSystem/Utils/StateMachine.h"

namespace uking::ui {

// Actual UI state-machine wrapper, vtable 0x7102474a70. Its holder at +8
// remains opaque; the original virtual methods access StateMachine at +0x30.
class Unk_7102474a70 {
public:
    virtual ~Unk_7102474a70();
    virtual void replaceState();
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
private:
    u64 _8[0x28 / sizeof(u64)];
    ksys::StateMachine mMachine;
};
KSYS_CHECK_SIZE_NX150(Unk_7102474a70, 0x58);

}  // namespace uking::ui
