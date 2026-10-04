#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace eui {

// The allocator hooks of nn::ui2d (Layout::SetAllocator): memory comes from a sead heap passed as the user data.
class NwAllocator {
public:
    // 0x7100be8f1c / 0x7100be8f70
    static void initialize(sead::Heap* heap);
    static void finalize();

    // 0x7100be8f38 / 0x7100be8f58 (placeholder names after the sibling CSV name ui2dDeallocateFunctionWithFindContainHeap)
    static void* ui2dAllocateFunction(size_t size, size_t alignment, void* heap);
    static void ui2dDeallocateFunction(void* ptr, void* heap);
};

}  // namespace eui
