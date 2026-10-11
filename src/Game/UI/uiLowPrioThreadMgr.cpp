#include "Game/UI/uiUnkSingletons.h"
#include <thread/seadThreadUtil.h>
#include "KingSystem/Utils/Thread/TaskThread.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(UiLowPrioThreadMgr)

UiLowPrioThreadMgr::~UiLowPrioThreadMgr() {
    _28->quitAndWaitDoneSingleThread(false);
    delete _28;
    _28 = nullptr;
    delete _30;
    _30 = nullptr;
    for (auto& handle : _38) {
        delete handle;
        handle = nullptr;
    }
}

// NON_MATCHING: the task init pointer stores are scheduled after the lane and batch stores.
void UiLowPrioThreadMgr::start(const sead::SafeString& name, sead::Heap* heap,
                               sead::CoreId core, s32 priority) {
    _30 = new (heap) ksys::util::TaskMgr(heap);
    _30->init<ksys::util::ManagedTask>(100, heap);
    for (auto& handle : _38)
        handle = new (heap) ksys::util::ManagedTaskHandle;
    _28 = new (heap) ksys::util::TaskThread(
        name, heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(priority),
        sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x100000, 32);
    ksys::util::TaskThread::InitArg arg{1, 1, heap, nullptr};
    _28->init(arg);
    _28->setAffinity(sead::CoreIdMask(core));
    _28->start();
}

// NON_MATCHING: handle lookup indexing and task request flag initialization differ.
ksys::util::ManagedTaskHandle* UiLowPrioThreadMgr::submitRequest(const Request& request) {
    ksys::util::ManagedTaskHandle* handle = nullptr;
    if (request.handle) {
        for (u32 i = 0; i < 100; ++i) {
            if (_38[i] == request.handle) {
                handle = request.handle;
                break;
            }
        }
    }
    if (!handle) {
        for (size_t i = 0; i < 100; ++i) {
            if (!_38[i]->isTaskAttached()) {
                handle = _38[i];
                break;
            }
        }
    }
    if (!handle)
        return nullptr;
    ksys::util::TaskRequest task_request;
    task_request.mSynchronous = false;
    task_request.mThread = _28;
    task_request.mDelegate = request.delegate;
    task_request.mUserData = request.user_data;
    task_request.mRemoveCallback = request.remove_callback;
    task_request.mPostRunCallback = request.post_run_callback;
    ksys::util::TaskMgrRequest mgr_request;
    mgr_request.task = request.task;
    mgr_request.request = &task_request;
    mgr_request.handle = handle;
    return _30->trySubmitRequest(mgr_request) ? handle : nullptr;
}

// 0x7100a6d978
void UiLowPrioThreadMgr::pause() {
    if (_28)
        _28->pause();
}

// 0x7100a6d988
void UiLowPrioThreadMgr::resume() {
    if (_28)
        _28->resume();
}

// 0x7100a6d998
void UiLowPrioThreadMgr::clearQueue() {
    if (_28)
        _28->clearQueue();
}

}  // namespace uking::ui
