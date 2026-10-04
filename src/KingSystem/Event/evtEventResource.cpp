#include "KingSystem/Event/evtEventResource.h"
#include <heap/seadHeap.h>

namespace ksys::evt {

// 0x7100dc3698
void EventResource::sub_7100DC3698() {
    _1e0 |= 0x10000;
}

void* eventFlowAlloc(size_t size, size_t alignment, void* userdata) {
    auto* heap = static_cast<sead::Heap*>(userdata);
    if (!heap)
        return nullptr;
    return heap->tryAlloc(size, static_cast<int>(alignment));
}

void eventFlowFree(void* ptr, void* userdata) {
    auto* heap = static_cast<sead::Heap*>(userdata);
    if (heap)
        heap->free(ptr);
}

}  // namespace ksys::evt
