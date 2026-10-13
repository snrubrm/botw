#include "KingSystem/Utils/NinStandardAllocatorHeap.h"
#include <prim/seadPtrUtil.h>

// NON_MATCHING: the native vtable uses a direct address; the ordinary class reference uses the GOT.
NinStandardAllocatorHeap::~NinStandardAllocatorHeap() {
    destruct_();
    mAllocator.Finalize();
}

void NinStandardAllocatorHeap::destroy() {
    void* start = mStart;
    sead::Heap* parent = mParent;
    this->~NinStandardAllocatorHeap();
    if (parent && parent->isFreeable())
        parent->free(start);
}

size_t NinStandardAllocatorHeap::adjust() {
    return 0;
}

void* NinStandardAllocatorHeap::tryAlloc(size_t size, s32 alignment) {
    if (alignment == 8)
        return mAllocator.Allocate(size);
    return mAllocator.Allocate(size, alignment);
}

void NinStandardAllocatorHeap::free(void* ptr) {
    mAllocator.Free(ptr);
}

void* NinStandardAllocatorHeap::resizeFront(void*, size_t) {
    return nullptr;
}

void* NinStandardAllocatorHeap::resizeBack(void*, size_t) {
    return nullptr;
}

void* NinStandardAllocatorHeap::tryRealloc(void* ptr, size_t size, s32) {
    return mAllocator.Reallocate(ptr, size);
}

void NinStandardAllocatorHeap::freeAll() {}

uintptr_t NinStandardAllocatorHeap::getStartAddress() const {
    return reinterpret_cast<uintptr_t>(mStart);
}

uintptr_t NinStandardAllocatorHeap::getEndAddress() const {
    return reinterpret_cast<uintptr_t>(mStart) + mSize;
}

size_t NinStandardAllocatorHeap::getSize() const {
    return mSize;
}

size_t NinStandardAllocatorHeap::getFreeSize() const {
    return 0;
}

size_t NinStandardAllocatorHeap::getMaxAllocatableSize(int) const {
    return 0;
}

bool NinStandardAllocatorHeap::isInclude(const void* ptr) const {
    const void* start = sead::PtrUtil::addOffset(mStart, sizeof(NinStandardAllocatorHeap));
    const void* end = sead::PtrUtil::addOffset(mStart, mSize);
    return start <= ptr && ptr < end;
}

bool NinStandardAllocatorHeap::isEmpty() const {
    return false;
}

bool NinStandardAllocatorHeap::isFreeable() const {
    return true;
}

bool NinStandardAllocatorHeap::isResizable() const {
    return false;
}

bool NinStandardAllocatorHeap::isAdjustable() const {
    return false;
}

void NinStandardAllocatorHeap::dump() const {}

void NinStandardAllocatorHeap::genInformation_(sead::hostio::Context* context) {
    sead::Heap::genInformation_(context);
}
