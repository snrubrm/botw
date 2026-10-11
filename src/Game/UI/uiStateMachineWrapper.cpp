#include "Game/UI/uiStateMachineWrapper.h"
#include "Game/UI/uiScreenChildMessage.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"

namespace uking::ui {

// NON_MATCHING: the receiver and state cleanup remain out-of-line.
Unk_7102474a28::~Unk_7102474a28() {
    deregisterReceiver(mAdapter);
}

bool Unk_7102474a28::sendMessage(const ksys::MesTransceiverId& dest,
                                const ksys::MessageType& type, void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(), dest,
                                                   type, user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_7102474a28::sendMessageOnProcessingThread(const ksys::MesTransceiverId& dest,
                                                  const ksys::MessageType& type,
                                                  void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), dest, type, user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_7102474a28::sendMessage(ksys::IMessageBroker& broker,
                                const ksys::MessageType& type, void* user_data, bool ack) {
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

bool Unk_7102474a28::sendMessageOnProcessingThread(ksys::IMessageBroker& broker,
                                                  const ksys::MessageType& type,
                                                  void* user_data, bool ack) {
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

ksys::MessageReceiverEx* Unk_7102474a28::getReceiver() { return &mAdapter; }


// NON_MATCHING: the natural destructor schedules its final argument before the virtual load.
Unk_7102474a70::~Unk_7102474a70() {
    mMachine._0->m3(&mMachine.mPrevious);
    mMachine._0->m3(&mMachine.mCurrent);
}

void Unk_7102474a70::changeStateFast(const ksys::StateBase* state) {
    mMachine.mCurrent = mMachine._0->setState(state);
    mMachine.mCurrent->enter();
}

void Unk_7102474a70::run() { mMachine.run(); }
void Unk_7102474a70::leaveState() { mMachine.sub_71010BFE64(); }
void Unk_7102474a70::enterState() { mMachine.mCurrent->enter(); }
void Unk_7102474a70::changeState(const ksys::StateBase* state) { mMachine.changeState(state); }
const ksys::StateBase* Unk_7102474a70::getState() const { return mMachine.getState(); }
const ksys::StateBase* Unk_7102474a70::getSubstate() const { return mMachine.mPrevState; }
s32 Unk_7102474a70::getRunCount() const { return mMachine.mCurrent->getRunCount(); }

bool Unk_7102474a70::reenter(void* arg) {
    if (!mMachine.mCurrent)
        Unk_7102474a70::replaceState();
    if (mMachine.mCurrent)
        return mMachine.mCurrent->reenter(arg);
    return false;
}

bool Unk_7102474a70::exec5(void* arg) {
    if (mMachine.mCurrent)
        return mMachine.mCurrent->exec5(arg);
    return false;
}

void Unk_7102474a70::exec6(void* arg) {
    if (mMachine.mCurrent)
        mMachine.mCurrent->exec6(arg);
}

}  // namespace uking::ui
