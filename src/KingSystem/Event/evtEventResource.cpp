#include "KingSystem/Event/evtEventResource.h"
#include <heap/seadHeap.h>

namespace ksys::evt {

// 0x7100dc3368
bool EventResource::areCameraAndModelAndXlinkReady() {
    if (_148 && !_148->finishLoad())
        return false;
    if ((_1e0 & 0x20) && !_1d3)
        return false;
    if (!(_1e0 & 0x100) && _1b8) {
        if (!_1b8->finishLoad(true))
            return false;
        _1e0 |= 0x100;
    }
    return true;
}

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
