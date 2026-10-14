#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/System/LayerMgrTask.h"
#include "KingSystem/System/PlayReportMgr.h"
#include <heap/seadHeapMgr.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <prim/seadPtrUtil.h>
#include <thread/seadThread.h>
#include "Game/gameUnkRttiPlaceholders.h"

// The heap helpers declared in HeapUtil.h are defined at the start of this TU in the original
// binary: they follow a static initializer, their statics sit right before LayerMgrTask::sInstance
// and they are out-of-line.
namespace ksys::util {

sead::Heap* tryCreateDualHeap(size_t size, const sead::SafeString& name, sead::Heap* heap1,
                              sead::Heap* heap2, sead::Heap::HeapDirection direction, bool b) {
    return sub_71010BDD10(size, name, heap1, heap2, direction, b);
}

DualHeap* DualHeap::create(size_t size, const sead::SafeString& name, Heap* parent1,
                           Heap* parent2, s32 alignment, HeapDirection direction, bool b) {
    return tryCreate(size, name, parent1, parent2, alignment, direction, b);
}

void* DualHeap::tryAlloc(size_t size, s32 alignment) {
    if (isLockEnabled())
        mCS.lock();
    void* ptr = sead::ExpHeap::tryAlloc(size, alignment);
    if (!ptr && mHeap2) {
        _118 += size;
        ptr = mHeap2->tryAlloc(size, alignment);
    }
    if (isLockEnabled())
        mCS.unlock();
    return ptr;
}

size_t DualHeap::sub_71010BF054() const {
    return sead::ExpHeap::getFreeSize();
}

size_t DualHeap::sub_71010BF058(s32 alignment) const {
    return sead::ExpHeap::getMaxAllocatableSize(alignment);
}

DualHeap::~DualHeap() {
    dispose_(nullptr, nullptr);
}

void DualHeap::free(void* ptr) {
    if (sead::ExpHeap::isInclude(ptr)) {
        sead::ExpHeap::free(ptr);
        return;
    }
    if (mHeap2 && mHeap2->isInclude(ptr))
        mHeap2->free(ptr);
}

void* DualHeap::resizeFront(void* ptr, size_t size) {
    if (sead::ExpHeap::isInclude(ptr))
        return sead::ExpHeap::resizeFront(ptr, size);
    if (mHeap2 && mHeap2->isInclude(ptr))
        return mHeap2->resizeFront(ptr, size);
    return nullptr;
}

void* DualHeap::resizeBack(void* ptr, size_t size) {
    if (sead::ExpHeap::isInclude(ptr))
        return sead::ExpHeap::resizeBack(ptr, size);
    if (mHeap2 && mHeap2->isInclude(ptr))
        return mHeap2->resizeBack(ptr, size);
    return nullptr;
}

// NON_MATCHING: the inherited isInclude call is devirtualized.
void* DualHeap::tryRealloc(void* ptr, size_t size, s32 alignment) {
    if (isInclude(ptr))
        return sead::ExpHeap::tryRealloc(ptr, size, alignment);
    if (mHeap2 && mHeap2->isInclude(ptr))
        return mHeap2->tryRealloc(ptr, size, alignment);
    return nullptr;
}

// NON_MATCHING: the inherited getSize call is devirtualized.
size_t DualHeap::getFreeSize() const {
    const size_t own_size = sead::ExpHeap::getFreeSize();
    const size_t other_size = mHeap2 ? mHeap2->getFreeSize() : 0;
    return sead::MathCalcCommon<size_t>::min(own_size + other_size, getSize());
}

// NON_MATCHING: the inherited getSize call is devirtualized.
size_t DualHeap::getMaxAllocatableSize(int alignment) const {
    const size_t own_size = sead::ExpHeap::getMaxAllocatableSize(alignment);
    const size_t other_size = mHeap2 ? mHeap2->getMaxAllocatableSize(alignment) : 0;
    return sead::MathCalcCommon<size_t>::min(sead::MathCalcCommon<size_t>::max(own_size, other_size), getSize());
}

bool DualHeap::isResizable() const {
    return false;
}

bool DualHeap::isAdjustable() const {
    return false;
}

void DualHeap::genInformation_(sead::hostio::Context* context) {
    if (isLockEnabled())
        sead::ExpHeap::genInformation_(context);
}

void DualHeap::makeMetaString_(sead::BufferedSafeString* string) {
    if (isLockEnabled())
        sead::Heap::makeMetaString_(string);
    else
        string->copy("Icon=CIRCLE_BLACK");
}

DualFrameHeap::~DualFrameHeap() {
    dispose_(nullptr, nullptr);
}

inline void* DualFrameHeap::getAreaStart_() const {
    return mDirection == cHeapDirection_Forward ?
               sead::PtrUtil::addOffset(mStart, sizeof(DualFrameHeap)) : mStart;
}

inline void* DualFrameHeap::getAreaEnd_() const {
    return sead::PtrUtil::addOffset(mStart, mDirection == cHeapDirection_Forward ?
                                              mSize : mSize - sizeof(DualFrameHeap));
}

// NON_MATCHING: final-class devirtualization and the native size-update memory barrier.
size_t DualFrameHeap::adjust() {
    if (!mParent)
        return mSize;
    sead::ConditionalScopedLock<sead::CriticalSection> lock(&mCS, isLockEnabled());
    Heap* parent = mParent;
    if (parent->isLockEnabled())
        parent->mCS.lock();
    size_t size;
    if (mDirection == cHeapDirection_Forward) {
        size = mSize;
        if (mState.mTailPtr == sead::PtrUtil::addOffset(mStart, size))
            size = adjustBack_();
    } else if (mState.mHeadPtr == mStart) {
        const size_t new_size = getEndAddress() - reinterpret_cast<uintptr_t>(mState.mTailPtr);
        if (mParent->resizeFront(mStart, new_size)) {
            mSize = new_size;
            mState.mHeadPtr = mState.mTailPtr;
            mStart = mState.mTailPtr;
            size = new_size;
        } else {
            size = mSize;
        }
    } else {
        size = mSize;
    }
    if (parent->isLockEnabled())
        parent->mCS.unlock();
    return size;
}

void* DualFrameHeap::tryAlloc(size_t size, s32 alignment) {
    if (isLockEnabled())
        mCS.lock();
    void* ptr = sead::FrameHeap::tryAlloc(size, alignment);
    if (!ptr && mHeap2) {
        if (_f8 == 0 && mHeap2->getName() == "EmergencyHeap" &&
            PlayReportMgr::instance() && PlayReportMgr::instance()->getReporter())
            reportEmergencyHeapUse(this);
        _f8 += size;
        ptr = mHeap2->tryAlloc(size, alignment);
    }
    if (isLockEnabled())
        mCS.unlock();
    return ptr;
}

// NON_MATCHING: the inherited getSize call is devirtualized.
size_t DualFrameHeap::getFreeSize() const {
    const size_t own_size = sead::FrameHeap::getFreeSize();
    const size_t other_size = mHeap2 ? mHeap2->getFreeSize() : 0;
    return sead::MathCalcCommon<size_t>::min(own_size + other_size, getSize());
}

// NON_MATCHING: the inherited getSize call is devirtualized.
size_t DualFrameHeap::getMaxAllocatableSize(int alignment) const {
    const size_t own_size = sead::FrameHeap::getMaxAllocatableSize(alignment);
    const size_t other_size = mHeap2 ? mHeap2->getMaxAllocatableSize(alignment) : 0;
    return sead::MathCalcCommon<size_t>::min(sead::MathCalcCommon<size_t>::max(own_size, other_size), getSize());
}

void DualFrameHeap::free(void* ptr) {
    if (sead::FrameHeap::isInclude(ptr)) {
        sead::FrameHeap::free(ptr);
        return;
    }
    if (mHeap2 && mHeap2->isInclude(ptr))
        mHeap2->free(ptr);
}

void DualFrameHeap::freeAll() {
    sead::ConditionalScopedLock<sead::CriticalSection> lock(&mCS, isLockEnabled());
    dispose_(nullptr, nullptr);
    mState.mHeadPtr = getAreaStart_();
    mState.mTailPtr = getAreaEnd_();
}

bool DualFrameHeap::isInclude(const void* ptr) const {
    const void* start = getAreaStart_();
    const void* end = getAreaEnd_();
    return start <= ptr && ptr < end;
}

bool DualFrameHeap::isEmpty() const {
    return mState.mHeadPtr == getAreaStart_() && mState.mTailPtr == getAreaEnd_();
}

bool DualFrameHeap::isAdjustable() const {
    return false;
}

void DualFrameHeap::genInformation_(sead::hostio::Context* context) {
    if (isLockEnabled())
        sead::Heap::genInformation_(context);
}

void DualFrameHeap::makeMetaString_(sead::BufferedSafeString* string) {
    if (isLockEnabled())
        sead::Heap::makeMetaString_(string);
    else
        string->copy("Icon=CIRCLE_BLACK");
}

// Name, layout and purpose unknown; this is stubbed in release builds
class DebugHeapHolder {
    SEAD_SINGLETON_DISPOSER(DebugHeapHolder)
    DebugHeapHolder() = default;

public:
    virtual ~DebugHeapHolder() = default;
    virtual sead::Heap* getHeap() { return nullptr; }
};

SEAD_SINGLETON_DISPOSER_IMPL(DebugHeapHolder)

// Name, layout and purpose unknown; this is stubbed in release builds
class DebugHeapHolder2 {
    SEAD_SINGLETON_DISPOSER(DebugHeapHolder2)
    DebugHeapHolder2() = default;

public:
    virtual ~DebugHeapHolder2() = default;
    virtual sead::Heap* getHeap() { return nullptr; }
};

SEAD_SINGLETON_DISPOSER_IMPL(DebugHeapHolder2)

sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap) {
    if (heap)
        return heap;

    if (!sead::ThreadMgr::instance())
        return nullptr;

    return getCurrentHeap();
}

void adjustHeapOrCurrentHeap(sead::Heap* heap) {
    if (!heap)
        heap = getCurrentHeap();
    heap->adjust();
}

sead::Heap* getCurrentHeap() {
    return sead::HeapMgr::instance()->getCurrentHeap();
}

sead::Heap* getDebugHeap() {
    if (!DebugHeapHolder::instance())
        return nullptr;
    return DebugHeapHolder::instance()->getHeap();
}

sead::Heap* getDebugHeap2() {
    if (DebugHeapHolder2::instance())
        return DebugHeapHolder2::instance()->getHeap();
    return getDebugHeap();
}

}  // namespace ksys::util

// NON_MATCHING: placeholder destructor; the original (0x71011f3674) also destroys members or bases
// this class does not declare yet.
Unk_7102513c38::~Unk_7102513c38() = default;

namespace vlt {
LayerMgrTask* LayerMgrTask::sInstance = nullptr;
}  // namespace vlt
