#include "Game/UI/euiNwAllocator.h"
#include <heap/seadHeap.h>

#include <nn/ui2d/Layout.h>

namespace eui {

// 0x7100be8f1c
void NwAllocator::initialize(sead::Heap* heap) {
    nn::ui2d::sub_710132B114(ui2dAllocateFunction, ui2dDeallocateFunction, heap);
}

// 0x7100be8f70
void NwAllocator::finalize() {
    nn::ui2d::sub_710132B114(nullptr, nullptr, nullptr);
}

// 0x7100be8f38
void* NwAllocator::ui2dAllocateFunction(size_t size, size_t alignment, void* heap) {
    return static_cast<sead::Heap*>(heap)->tryAlloc(size, alignment);
}

// 0x7100be8f58
void NwAllocator::ui2dDeallocateFunction(void* ptr, void* heap) {
    static_cast<sead::Heap*>(heap)->free(ptr);
}

}  // namespace eui
