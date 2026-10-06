#include "KingSystem/Event/evtEventResource.h"
#include <heap/seadHeap.h>
#include "KingSystem/Event/evtResourceFlowchart.h"
#include "KingSystem/Event/evtResourceTimeline.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resTempResourceLoader.h"

namespace ksys::evt {

void EventResource::initTimeline(const sead::SafeString& event_name) {
    mTimeline = new (mHeap, 8) ResourceTimeline;
    mTimeline->mName.copy(event_name);
    loadEventPack();
}

void EventResource::loadEventPack() {
    sead::FixedSafeString<64> path;
    if (mFlowchart)
        path.format("Event/%s.beventpack", mFlowchart->mName.cstr());
    else if (mTimeline)
        path.format("Event/%s.beventpack", mTimeline->mName.cstr());
    else
        return;

    if (!res::ResourceMgrTask::instance()->getResourceSize(path, nullptr))
        return;

    res::TempResourceLoader::LoadArg arg;
    arg.retry_on_failure = true;
    arg.use_handle = true;
    arg.load_req.mRequester = "EventResource";
    arg.load_req._28 = false;
    arg.load_req.mPath = path;
    arg.load_req.mLoadDataAlignment = 0x100;
    arg.load_req._26 = false;

    res::TempResourceLoader::InitArg init_arg{};
    mTempResourceLoader = new (mHeap, 8) res::TempResourceLoader;
    res::ResourceMgrTask::instance()->initTempResourceLoader(mTempResourceLoader, init_arg);
    mTempResourceLoader->requestLoad(arg);
    _1e0 |= 0x4000;
}

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
