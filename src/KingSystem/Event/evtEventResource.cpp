#include "KingSystem/Event/evtEventResource.h"
#include <heap/seadHeap.h>
#include "KingSystem/Resource/resLoadRequest.h"

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

// 0x7100dc421c
void EventResource::EventAddExtraModelRes_stuff(void* a1) {
    auto* handle = static_cast<res::Handle*>(a1);
    if (!handle->requestedLoad() && _1b0 && (_1e0 & 0x40) && _158.getUnit()) {
        res::SimplePackedLoadRequest request;
        request.mRequester = "EventAddExtraModelRes";
        request.mPack = &_158;
        handle->load(sead::SafeString::cEmptyString, &request);
    }
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
