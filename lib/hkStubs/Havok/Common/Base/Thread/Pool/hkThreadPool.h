#pragma once

#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Havok/Common/Base/hkBase.h>

class hkMemoryAllocator;
class hkTaskQueue;
struct hkTimerData;

// Slot order from the thread pool vtable 0x7102523450 (constructed by 0x710132084c): processAllJobs
// 0x7101586a94, processTaskQueue 0x7101586b08, isProcessing 0x7101586bec, waitForCompletion
// 0x7101586b7c, getNumThreads 0x7101586cdc, setNumThreads 0x7101586ce4, appendTimerData 0x7101586c00,
// clearTimerData 0x7101586ca0, gcThreadMemoryOnNextCompletion 0x7101586a84.
class hkThreadPool : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkThreadPool)

    virtual void processAllJobs(hkJobQueue* queue, hkJobType firstJobType = HK_JOB_TYPE_MAX) = 0;
    virtual void processTaskQueue(hkTaskQueue* taskQueue) = 0;
    virtual bool isProcessing() const = 0;
    virtual void waitForCompletion() = 0;
    virtual int getNumThreads() const = 0;
    virtual void setNumThreads(int numThreads) = 0;
    virtual void appendTimerData(hkArrayBase<hkTimerData>& timerData,
                                 hkMemoryAllocator& alloc) = 0;
    virtual void clearTimerData() = 0;
    virtual void gcThreadMemoryOnNextCompletion() = 0;
};
