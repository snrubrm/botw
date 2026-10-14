#pragma once

#include "KingSystem/Utils/StateMachine.h"

namespace uking::ui {

// UI state-machine wrapper, vtable 0x7102474a70 (ScreenChild) / 0x710250a3a8 (Screen). Its holder at +8
// remains opaque; the original virtual methods access StateMachine at +0x30.
// A template over the owner: the Screen TU has its own copy of every method (0x71010ad0e4..) with
// its own vtables, while the ScreenChild copy lives at 0x71009327fc.
template <typename Owner>
class Unk_7102474a70 {
public:
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
    u64 _8[0x28 / sizeof(u64)];
    ksys::StateMachine mMachine;
};


}  // namespace uking::ui
