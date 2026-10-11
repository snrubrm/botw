#include "Game/gameOpenWorldStageMessage.h"
#include "KingSystem/Utils/Thread/MessageDispatcherBase.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"

namespace uking {

const ksys::StateBase& Unk_710245b740::getState() const {
    return *mState;
}

Unk_710245b710::~Unk_710245b710() = default;

// NON_MATCHING: the adapter address is computed before the dispatcher call.
Unk_710245b4f8::~Unk_710245b4f8() {
    deregisterReceiver(mAdapter);
}

bool Unk_710245b4f8::sendMessage(const ksys::MesTransceiverId& dest,
                                 const ksys::MessageType& type, void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(), dest, type,
                                                  user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_710245b4f8::sendMessageOnProcessingThread(const ksys::MesTransceiverId& dest,
                                                   const ksys::MessageType& type, void* user_data,
                                                   bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), dest, type, user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_710245b4f8::sendMessage(ksys::IMessageBroker& broker, const ksys::MessageType& type,
                                 void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(),
                                                  *getRegister(broker), type, user_data, ack, false);
    if (sent) {
        int count = broker.countTransceivers();
        if (count > 0) {
            do {
                mAdapter.setFlag(ack);
            } while (--count);
        }
    }
    return sent;
}

bool Unk_710245b4f8::sendMessageOnProcessingThread(ksys::IMessageBroker& broker,
                                                   const ksys::MessageType& type, void* user_data,
                                                   bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), *getRegister(broker), type, user_data, ack, false);
    if (sent) {
        int count = broker.countTransceivers();
        if (count > 0) {
            do {
                mAdapter.setFlag(ack);
            } while (--count);
        }
    }
    return sent;
}

ksys::MessageReceiverEx* Unk_710245b4f8::getReceiver() {
    return &mAdapter;
}

// NON_MATCHING: the final state cleanup argument is scheduled before the frame restore.
Unk_710245b540::~Unk_710245b540() = default;

void Unk_710245b540::run() {
    mMachine.run();
}

// NON_MATCHING: the bool state callback result requires conversion to the receiver's int result.
int Unk_710245b540::receive(const ksys::Message& message) {
    if (Unk_710245b690::reenter(const_cast<ksys::Message*>(&message)))
        return 1;
    return Unk_710245b690::exec5(const_cast<ksys::Message*>(&message));
}

void Unk_710245b540::receive(const ksys::MessageAck& ack) {
    Unk_710245b690::exec6(const_cast<ksys::MessageAck*>(&ack));
}

void Unk_710245b740::enter() {
    mRunCount = 0;
    mState->enter(mOwner);
}

void Unk_710245b740::run() {
    mState->run(mOwner);
    ++mRunCount;
}

void Unk_710245b740::leave() {
    mState->leave(mOwner);
    mState = nullptr;
    mRunCount = 0;
}

ksys::StateMachine::Unk2* Unk_710245b710::setState(const ksys::StateBase* state) {
    mBinding.mState = state;
    return &mBinding;
}

void Unk_710245b690::replaceState() {
    if (mMachine.mNextState) {
        mMachine.mCurrent = mMachine._0->setState(mMachine.mNextState);
        mMachine.mCurrent->enter();
        mMachine.mNextState = nullptr;
    }
}

void Unk_710245b690::changeStateFast(const ksys::StateBase* state) {
    mMachine.mCurrent = mMachine._0->setState(state);
    mMachine.mCurrent->enter();
}

void Unk_710245b690::run() {
    mMachine.run();
}

void Unk_710245b690::leaveState() {
    mMachine.sub_71010BFE64();
}

void Unk_710245b690::enterState() {
    mMachine.mCurrent->enter();
}

void Unk_710245b690::changeState(const ksys::StateBase* state) {
    mMachine.changeState(state);
}

const ksys::StateBase* Unk_710245b690::getState() const {
    return mMachine.getState();
}

const ksys::StateBase* Unk_710245b690::getSubstate() const {
    return mMachine.mPrevState;
}

s32 Unk_710245b690::getRunCount() const {
    return mMachine.mCurrent->getRunCount();
}

bool Unk_710245b690::reenter(void* arg) {
    if (!mMachine.mCurrent)
        Unk_710245b690::replaceState();
    if (mMachine.mCurrent)
        return mMachine.mCurrent->reenter(arg);
    return false;
}

bool Unk_710245b690::exec5(void* arg) {
    if (mMachine.mCurrent)
        return mMachine.mCurrent->exec5(arg);
    return false;
}

void Unk_710245b690::exec6(void* arg) {
    if (mMachine.mCurrent)
        mMachine.mCurrent->exec6(arg);
}

}  // namespace uking
