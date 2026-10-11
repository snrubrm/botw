#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeapMgr.h>

namespace gsys {

// Native BF63F0, BF738C and C0334C construct this single heap pointer on
// the stack before calling C7CEB0. There is no vtable or additional storage.
class MemAllocator {
public:
    // Inline-only in the original; construction is inferred from those three
    // independent producers, including their current-heap fallback.
    explicit MemAllocator(sead::Heap* heap)
        : mHeap(heap ? heap : sead::HeapMgr::sInstancePtr->getCurrentHeap()) {}

    void* tryAlloc(size_t size, u32 alignment);

private:
    sead::Heap* mHeap;
};
static_assert(sizeof(MemAllocator) == 8, "MemAllocator size");

}  // namespace gsys
