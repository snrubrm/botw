#include "KingSystem/Utils/StateMachine.h"

namespace ksys {

StateBase sUnk_710250bcd8{-1, nullptr};

StateMachine::StateMachine(Unk1* unk, const StateBase& state) : _0(unk) {
    if (state.mId != -1)
        mNextState = &state;
}

// NON_MATCHING: the null-state select has swapped operands and the global's address is loaded first
const StateBase* StateMachine::getState() const {
    if (mCurrent)
        return &mCurrent->getState();
    return mNextState ? mNextState : &sUnk_710250bcd8;
}

void StateMachine::run() {
    _0->m3(&mPrevious);
    if (mCurrent)
        mCurrent->run();
}

void StateMachine::sub_71010BFE64() {
    if (!mCurrent)
        return;
    mPrevState = &mCurrent->getState();
    mCurrent->leave();
    mPrevious = mCurrent;
    mCurrent = nullptr;
}

void StateMachine::changeState(const StateBase* state) {
    mNextState = state;
    if (mCurrent) {
        sub_71010BFE64();
        if (!mNextState)
            return;
    }
    mCurrent = _0->setState(mNextState);
    mCurrent->enter();
    mNextState = nullptr;
}


s32 StateBase::getId() const {
    return mId;
}

const char* StateBase::getName() const {
    return mName;
}

void StateBase::enter(void*) const {}

void StateBase::run(void*) const {}

void StateBase::leave(void*) const {}

bool StateBase::exec4(void*, void*) const {
    return false;
}

bool StateBase::return0(void*, void*) const {
    return false;
}

void StateBase::null(void*, void*) const {}

}  // namespace ksys
