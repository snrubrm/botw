#pragma once

#include <basis/seadTypes.h>
#include <nn/account.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadDelegate.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadThread.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// Name from the CSV. The uploader constructs a 0x150-byte thread at 0x7100a8d188;
// calc_ polls network availability under the critical section at +0x110.
class NexThread : public sead::Thread {
public:
    NexThread(const sead::SafeString& name, sead::Heap* heap)
        : sead::Thread(name, heap, 16, sead::MessageQueue::BlockType::NonBlocking, 0x7fffffff,
                       0x2000, 0x20),
          mInterval(sead::TickSpan::makeFromSeconds(1).toS64() / 2) {}
    ~NexThread() override;

    /* 0x100 */ sead::TickSpan mInterval;
    /* 0x108 */ bool mNetworkAvailable = false;
    /* 0x110 */ sead::CriticalSection mCS;

protected:
    void calc_(sead::MessageQueue::Element msg) override;
};
KSYS_CHECK_SIZE_NX150(NexThread, 0x150);

// Placeholder name and namespace (CSV PosTrackerUploader::*; singleton at 0x71025f64c8, size 0x130, the singleton
// disposer is the first member). Uploads the player position tracking data through the NEX library (the heaps are
// named "NexHeap" / "CurlHeap"). Only the singleton functions, the heaps and the state queries are decompiled.
class PosTrackerUploader {
    SEAD_SINGLETON_DISPOSER(PosTrackerUploader)
    PosTrackerUploader();
    ~PosTrackerUploader();

public:
    // 0x7100a8be0c (CSV initHeaps): creates the NEX heap (1 MiB), a 6 MiB buffer in `parent` and the second heap
    // (1 MiB). `value` is stored at +0x118 on success.
    bool initHeaps(sead::Heap* parent, s32 value);

    // 0x7100a8c368 (CSV x): 1 while a callback is queued at +0xe0, else the state at +0xf0 (read under the lock at +0xa0).
    s32 sub_7100A8C368();

    // 0x7100a8c3b8 (CSV queueUpload): queues doUpload on the low priority thread; false if one is already pending or running.
    bool queueUpload();
    // Upload entry points used by the job at 0x7100a8f2dc (declarations only).
    bool sub_7100A8C770(const void* buffer, u32 size, u64 nex_id, s32 block, bool hard_mode);
    bool sub_7100A8CC48(const void* buffer, u32 size, u64 nex_id, bool hard_mode);
    bool queueCleanUp();
    // 0x7100a8d2fc (placeholder name): gets the network service account ID and loads its ID token
    // (up to 0xc00 bytes) for the current user, refreshing the token cache first.
    bool sub_7100A8D2FC(nn::account::NetworkServiceAccountId* id, char* token);

    sead::Heap* getHeap() const { return mHeap; }
    sead::Heap* getHeap2() const { return mHeap2; }

private:
    bool doUpload(void* arg);
    // 0x7100a8c6b8 (CSV doCleanUp): the low priority job body queued by queueCleanUp.
    bool doCleanUp(void* arg);

    /* 0x20 */ sead::Heap* mHeap = nullptr;
    /* 0x28 */ void* mBuffer = nullptr;
    /* 0x30 */ sead::Heap* mHeap2 = nullptr;
    /* 0x38 */ NexThread* _38 = nullptr;
    /* 0x40 */ sead::Delegate1R<PosTrackerUploader, void*, bool> mUploadDelegate;
    /* 0x60 */ sead::CriticalSection mCS1;
    /* 0xa0 */ sead::CriticalSection mCS2;
    /* 0xe0 */ bool (PosTrackerUploader::*_e0)() = nullptr;
    /* 0xf0 */ s32 _f0 = 0;
    /* 0xf4 */ bool _f4 = false;
    /* 0xf5 */ bool _f5 = false;
    /* 0xf6 */ bool _f6 = true;
    /* 0xf8 */ void* _f8 = nullptr;
    /* 0x100 */ void* _100 = nullptr;
    /* 0x108 */ void* _108 = nullptr;
    /* 0x110 */ u16 _110 = 0;
    /* 0x112 */ u16 _112 = 0xffff;
    /* 0x114 */ u16 _114 = 0xffff;
    /* 0x116 */ u16 _116 = 0;
    /* 0x118 */ s32 _118 = -1;
    /* 0x120 */ void* _120 = nullptr;
    /* 0x128 */ void* _128 = nullptr;
};
static_assert(sizeof(PosTrackerUploader) == 0x130);

// 0x7100a8c144 / 0x7100a8c16c / 0x7100a8c190 / 0x7100a8c1b8 (placeholder names; only used through function pointers, probably
// the allocator callbacks of the NEX library): allocate (8 byte aligned) from / free to the first and the second heap.
void* sub_7100A8C144(size_t size);
void sub_7100A8C16C(void* ptr);
void* sub_7100A8C190(size_t size);
void sub_7100A8C1B8(void* ptr);

}  // namespace ksys
