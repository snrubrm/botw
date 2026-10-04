#include "Game/UI/euiNwAllocator.h"
#include <heap/seadHeap.h>

namespace nn::ui2d {
// 0x710132b114 (CSV unnamed; placeholder name): logs and calls Layout::SetAllocator (library code; declared here until the
// SDK header has it)
void sub_710132B114(void* (*allocate)(size_t, size_t, void*), void (*free)(void*, void*), void* user_data);
}  // namespace nn::ui2d

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
