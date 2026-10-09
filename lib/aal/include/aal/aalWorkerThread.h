#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include <thread/seadThread.h>

namespace aal {

/// A task that a WorkerThread runs. TODO: only what the WorkerThread uses.
class WorkerTask {
public:
    virtual ~WorkerTask() = default;
    /// `is_quitting`: the thread is quitting (the task has to finish quickly).
    // Native FinalOutputMeasure and AuxBusRootFx tables name this slot.
    virtual void workerThreadProc_(bool is_quitting) = 0;

    /// The number of times the task was added to a thread and has not been run yet.
    sead::Atomic<s32> mNumPending;
};

/// Is called by the WorkerThread around every message (purpose unknown).
class WorkerThreadCallback {
public:
    virtual ~WorkerThreadCallback() = default;
    virtual void beforeMessage() = 0;
    virtual void afterMessage() = 0;
};

/// Runs the tasks that are added to it (a message of the thread is a pointer to the task).
class WorkerThread : public sead::Thread {
public:
    WorkerThread(const sead::SafeString& name, sead::Heap* heap, s32 priority, s32 stack_size,
                 s32 message_queue_size);
    ~WorkerThread() override;

    /// False if the thread is quitting or the message queue is full.
    bool addTask(WorkerTask* task);

protected:
    void calc_(sead::MessageQueue::Element msg) override;

private:
    WorkerThreadCallback* mCallback = nullptr;
};
static_assert(sizeof(WorkerThread) == 0x108, "aal::WorkerThread size mismatch");

}  // namespace aal
