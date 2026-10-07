#include "aal/aalWorkerThread.h"

namespace aal {

// 0x7100b7d074
WorkerThread::WorkerThread(const sead::SafeString& name, sead::Heap* heap, s32 priority, s32 stack_size,
                           s32 message_queue_size)
    : Thread(name, heap, priority, sead::MessageQueue::BlockType::Blocking, 0x7fffffff, stack_size,
             message_queue_size) {}

// The body keeps the vtable pointer stores of the destructor (a defaulted or empty destructor does not store them).
// 0x7100b7d0c8 (D2) / 0x7100b7d11c (D0)
WorkerThread::~WorkerThread() {
    if (!isDone())
        quitAndWaitDoneSingleThread(false);
}

// 0x7100b7d178
bool WorkerThread::addTask(WorkerTask* task) {
    if (mState == State::cQuitting || mState == State::cTerminated)
        return false;

    if (!sendMessage(reinterpret_cast<sead::MessageQueue::Element>(task), sead::MessageQueue::BlockType::NonBlocking))
        return false;

    task->mNumPending.increment();
    return true;
}

// 0x7100b7d1dc
void WorkerThread::calc_(sead::MessageQueue::Element msg) {
    if (mCallback)
        mCallback->beforeMessage();

    if (msg) {
        auto* task = reinterpret_cast<WorkerTask*>(msg);
        task->run(mState == State::cQuitting);
        task->mNumPending.decrement();
    }

    if (mCallback)
        mCallback->afterMessage();
}

}  // namespace aal
