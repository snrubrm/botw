#include "KingSystem/System/PosTrackerUploader.h"
#include <heap/seadExpHeap.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Utils/Thread/LowPrioThreadMgr.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(PosTrackerUploader)

PosTrackerUploader::PosTrackerUploader() = default;

PosTrackerUploader::~PosTrackerUploader() {
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
    if (mBuffer) {
        delete mBuffer;
        mBuffer = nullptr;
    }
    if (mHeap2) {
        mHeap2->destroy();
        mHeap2 = nullptr;
    }
}

s32 PosTrackerUploader::sub_7100A8C368() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS2);
    if (_e0)
        return 1;
    return _f0;
}

void* sub_7100A8C144(size_t size) {
    return PosTrackerUploader::instance()->getHeap()->tryAlloc(size, 8);
}

void sub_7100A8C16C(void* ptr) {
    PosTrackerUploader::instance()->getHeap()->free(ptr);
}

void* sub_7100A8C190(size_t size) {
    return PosTrackerUploader::instance()->getHeap2()->tryAlloc(size, 8);
}

void sub_7100A8C1B8(void* ptr) {
    PosTrackerUploader::instance()->getHeap2()->free(ptr);
}

// NON_MATCHING: only the order / pairing of the stores of the delegate (the original stores the zero adjustment at +0x58
// first, then {instance, function} as one pair) and of the request fields.
bool PosTrackerUploader::queueUpload() {
    if (sub_7100A8C368() == 1)
        return false;

    mUploadDelegate = sead::Delegate1R<PosTrackerUploader, void*, bool>(this, &PosTrackerUploader::doUpload);
    _f0 = 1;

    util::LowPrioThreadMgr::Request request;
    request.lane_id = 1;
    request.flags.setDirect(4);
    request.delegate = &mUploadDelegate;
    if (evt::submitLowPriorityRequest(request))
        return true;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS2);
    _f0 = 2;
    _e0 = nullptr;
    return false;
}

// NON_MATCHING: only the schedule of the success path (the original materialises the return value 1 before the store
// to +0x118).
bool PosTrackerUploader::initHeaps(sead::Heap* parent, s32 value) {
    mHeap = sead::ExpHeap::tryCreate(0x100000, "NexHeap", parent, 8, sead::Heap::cHeapDirection_Forward, true);
    if (!mHeap)
        return false;

    mBuffer = parent->tryAlloc(0x600000, 0x1000);
    if (mBuffer) {
        mHeap2 = sead::ExpHeap::tryCreate(0x100000, "CurlHeap", parent, 8, sead::Heap::cHeapDirection_Forward, true);
        if (mHeap2) {
            _118 = value;
            return true;
        }
        parent->free(mBuffer);
        mBuffer = nullptr;
    }

    mHeap->destroy();
    mHeap = nullptr;
    return false;
}

}  // namespace ksys
