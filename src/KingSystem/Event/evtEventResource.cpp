#include "KingSystem/Event/evtEventResource.h"
#include <heap/seadHeap.h>
#include "KingSystem/Event/evtInfoData.h"
#include "KingSystem/Event/evtResourceFlowchart.h"
#include "KingSystem/Event/evtResourceTimeline.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resTempResourceLoader.h"

namespace ksys::evt {


bool EventResource::invokedParseExtraModelRes() {
    _158.parseResource(nullptr);
    if (_158.isSuccess())
        _1b0 = _158.getModelRes();
    _1d3 = true;
    return true;
}

void EventResource::initFlowchart(const sead::SafeString& event_name,
                                  const sead::SafeString& entry_point) {
    auto* flowchart = new (mHeap, 8) ResourceFlowchart;
    mFlowchart = flowchart;
    flowchart->mName.copy(event_name);
    flowchart->mEntryPoint.copy(entry_point);
    loadEventPack();
}

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

void EventResource::loadEventResources(bool a1) {
    if (mTimeline) {
        al::ByamlIter info;
        InfoData::instance()->getEntry(&info, mTimeline->mName, mTimeline->mName);
        mTimeline->loadEventFlow(mHeap, info, _1d8);
        auto* bgm = new (mHeap, 8) EventBgmInfo;
        _1c0 = bgm;
        bgm->init(mTimeline->mName, mHeap, true, &info, _1d8);
        loadCommon_DemoAndModel(mTimeline->mName, &info, _1d8, a1);
    }
    if (mFlowchart) {
        al::ByamlIter info;
        InfoData::instance()->getEntry(&info, mFlowchart->mName, mFlowchart->mEntryPoint);
        mFlowchart->loadEventFlow(mHeap, _1d8);
        auto* bgm = new (mHeap, 8) EventBgmInfo;
        _1c0 = bgm;
        bgm->init(mFlowchart->mName, mHeap, false, &info, _1d8);
        loadCommon_DemoAndModel(mFlowchart->mName, &info, _1d8, a1);
    }
}

bool EventResource::processResourceLoad(bool a1) {
    _1d0 = 0;
    _1e0 = a1 ? (_1e0 | 0x20000) : (_1e0 & ~0x20000u);

    if (_1e0 & 0x11000) {
        if (mTempResourceLoader) {
            delete mTempResourceLoader;
            mTempResourceLoader = nullptr;
        }
        return true;
    }

    if (!(_1e0 & 0x2000)) {
        bool wait = false;
        if (_1e0 & 0x4000) {
            if (mTempResourceLoader->getResourceForLoadRequest(nullptr)) {
                _1d8 = mTempResourceLoader->getHandle();
            } else if (mTempResourceLoader->isLoading() && !(_1e0 & 0x10000)) {
                wait = true;
            } else {
                if (mTempResourceLoader)
                    delete mTempResourceLoader;
                mTempResourceLoader = nullptr;
                _1e0 |= 0x1000;
            }
        }
        if (!wait) {
            if (_1e0 & 0x1000)
                return true;
            loadEventResources(a1);
            _1e0 |= 0x2000;
        }
        _1d0 |= 0x200;
    }

    if ((_1e0 & 0x2000) && finishLoad(false))
        return true;
    return false;
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
