#include "KingSystem/Resource/resResourceMgrTask.h"
#include <framework/seadHeapPolicies.h>
#include <framework/seadTaskID.h>
#include <resource/seadResourceMgr.h>
#include <resource/seadSZSDecompressor.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Framework/frmWorkerSupportThreadMgr.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/Resource/resCache.h"
#include "KingSystem/Resource/resCompactedHeap.h"
#include "KingSystem/Resource/resControlTask.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resMemoryTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resTextureHandleList.h"
#include "KingSystem/Resource/resArchiveWork.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/System/KingEditor.h"
#include "KingSystem/System/OverlayArenaSystem.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/System/Patrol.h"
#include "KingSystem/System/ProductReporter.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/GameTaskThread.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/TaskQueueBase.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::res {

static bool sUnk_71026529C8;

namespace {
class ClearCachesTaskData : public util::TaskData {
    SEAD_RTTI_OVERRIDE(ClearCachesTaskData, util::TaskData)
public:
    virtual ~ClearCachesTaskData() = default;

    bool _8;
    s32 _c;
    sead::SafeString mStr;
};
KSYS_CHECK_SIZE_NX150(ClearCachesTaskData, 0x20);
}  // namespace

void ResourceMgrTask::setInstance(ResourceMgrTask* task) {
    if (!sInstance) {
        sInstance = task;
        task->mInstancePtrClearer.mClearOnDestruction = true;
    }
}

ResourceMgrTask::ResourceMgrTask(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "res::ResourceMgrTask"),
      mSzsDecompressorCS(arg.heap_array->getPrimaryHeap()),
      mCounter(arg.heap_array->getPrimaryHeap()), mTask(arg.heap_array->getPrimaryHeap()) {
    mArenas.initOffset(OverlayArena::getListNodeOffset());
    mUnits.initOffset(ResourceUnit::getResMgrUnitListNodeOffset());
    mBfResList.initOffset(0x188);  // TODO: replace this with a get-offset call
    mSystemCalcFn.bind(this, &ResourceMgrTask::callSystemCalc_);
    mFileDevicePrefixes.initOffset(FileDevicePrefix::getListNodeOffset());
}

ResourceMgrTask::~ResourceMgrTask() {
    util::safeDelete(mTexHandleList);
    util::safeDelete(mTexHandleMgr);
    util::safeDeleteThread(mCompactionThread);

    if (mCompactedHeapMip0) {
        mCompactedHeapMip0->destroy();
        util::safeDeleteArray(mCompactedHeapMip0Buffer);
    }

    if (mCompactedHeapMain) {
        mCompactedHeapMain->destroy();
        util::safeDeleteArray(mCompactedHeapMainBuffer);
        mCompactedHeapMainSeadHeap->destroy();
    }

    util::safeDeleteArray(mCompactedHeapMainBuffer2);
    util::safeDelete(mOffsetReadBuf);
    mExtensions2.freeBuffer();
    mExtensions1.freeBuffer();

    util::safeDeleteThread(mMovableMemoryThread);
    util::safeDeleteThread(mResourceMemoryThread);
    util::safeDeleteThread(mResourceControlThread);
    util::safeDeleteThread(mResourceLoadingThread);
    util::safeDelete(mTask3);
    util::safeDelete(mTask2);
    util::safeDelete(mTask1);
    util::safeDelete(mControlTask);

    if (mResourceMemoryTaskMgr) {
        mResourceMemoryTaskMgr->finalize();
        util::safeDelete(mResourceMemoryTaskMgr);
    }

    if (mResourceControlTaskMgr) {
        mResourceControlTaskMgr->finalize();
        util::safeDelete(mResourceControlTaskMgr);
    }

    util::safeDelete(mEntryFactoryBase);

    mResSystemHeap->destroy();
}

void ResourceMgrTask::insertOverlayArena(OverlayArena* arena) {
    auto lock = sead::makeScopedLock(mArenasCS);
    if (!mArenas.isNodeLinked(arena)) {
        mArenas.pushBack(arena);
        stubbedLogFunction();
    }
}

util::TaskThread* ResourceMgrTask::makeResourceLoadingThread(sead::Heap* heap,
                                                             bool use_game_task_thread) {
    if (use_game_task_thread) {
        return new (heap) util::GameTaskThread(
            "Resource Loading", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(19),
            sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0xfa000, 32);
    }

    return new (heap) util::TaskThread(
        "Resource Loading", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(19),
        sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0xa000, 32);
}

void ResourceMgrTask::clearAllCaches(OverlayArena* arena) {
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_5));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_4));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_3));

    MemoryTaskRequest req;
    req.mLaneId = u8(LaneId::_9);
    req.mHasHandle = true;
    req.mSynchronous = false;
    req.mThread = mResourceMemoryThread;
    req.mDelegate = &mClearAllCachesFn;
    req.mName = "ClearAllCaches";
    req.mData_8 = false;
    req.mData_c = -1;
    req.mData_mStr = arena->getHeap()->getName();

    util::TaskMgrRequest task_mgr_request;
    task_mgr_request.request = &req;
    mResourceMemoryTaskMgr->submitRequest(task_mgr_request);
}

OverlayArena* ResourceMgrTask::getTexHandleMgrArena() const {
    return mTexHandleMgr->getArchiveWork()->getArena();
}

bool ResourceMgrTask::isDefragDone() const {
    return mTask2->getStatus() == util::Task::Status::PostFinishCallback;
}

f32 ResourceMgrTask::getDefragProgress() const {
    auto lock = sead::makeScopedLock(mArenasCS);
    if (_4c8 == -1)
        return 0;
    return f32(_4cc) / f32(_4c8);
}

void ResourceMgrTask::registerFactory(sead::ResourceFactory* factory,
                                      const sead::SafeString& name) {
    auto lock = sead::makeScopedLock(mFactoryCS);
    sead::ResourceMgr::instance()->registerFactory(factory, name);
}

void ResourceMgrTask::unregisterFactory(sead::ResourceFactory* factory) {
    auto lock = sead::makeScopedLock(mFactoryCS);
    sead::ResourceMgr::instance()->unregisterFactory(factory);
}

void ResourceMgrTask::cancelTasks() {
    stubbedLogFunction();
    stubbedLogFunction();
    mMovableMemoryThread->cancelTasks(u8(LaneId::_1));
    mMovableMemoryThread->cancelTasks(u8(LaneId::_0));
    mMovableMemoryThread->cancelTasks(u8(LaneId::_3));
    mMovableMemoryThread->cancelTasks(u8(LaneId::_4));

    stubbedLogFunction();
    stubbedLogFunction();
    mResourceControlThread->cancelTasks(u8(LaneId::_0));
    mResourceControlThread->cancelTasks(u8(LaneId::_1));
    mResourceControlThread->cancelTasks(u8(LaneId::_2));

    stubbedLogFunction();
    stubbedLogFunction();
    mResourceMemoryThread->cancelTasks(u8(LaneId::_1));
    mResourceMemoryThread->cancelTasks(u8(LaneId::_2));
    mResourceMemoryThread->cancelTasks(u8(LaneId::_3));
    mResourceMemoryThread->cancelTasks(u8(LaneId::_4));
    mResourceMemoryThread->cancelTasks(u8(LaneId::_5));
    mResourceMemoryThread->cancelTasks(u8(LaneId::_6));

    stubbedLogFunction();
    stubbedLogFunction();
    mResourceLoadingThread->cancelTasks(u8(LaneId::_0));
    mResourceLoadingThread->cancelTasks(u8(LaneId::_1));
    mResourceLoadingThread->cancelTasks(u8(LaneId::_2));

    stubbedLogFunction();
    stubbedLogFunction();
}

void ResourceMgrTask::waitForTaskQueuesToEmpty() {
    if (mResourceControlThread->isPaused() || mResourceMemoryThread->isPaused() ||
        mResourceLoadingThread->isPaused()) {
        return;
    }

    mResourceControlThread->waitForQueueToEmpty();
    mResourceMemoryThread->waitForQueueToEmpty();
    mResourceLoadingThread->waitForQueueToEmpty();
}

s32 ResourceMgrTask::getNumActiveTasksOnResLoadingThread() const {
    return mResourceLoadingThread->getNumActiveTasks();
}

OffsetReadFileDevice* ResourceMgrTask::getOffsetReadFileDevice() const {
    return mOffsetReadFileDevice;
}

sead::ArchiveFileDevice* ResourceMgrTask::getArchiveFileDev1() {
    return &mArchiveFileDev1;
}

void ResourceMgrTask::controlField9c0d88(bool off) {
    if (off) {
        _9c0d88.decrement();
        static_cast<void>(_9c0d88.load());
    } else {
        _9c0d88.increment();
    }

    mFlags.change(Flag::_400, _9c0d88 <= 0);
}

void ResourceMgrTask::setFlag2000Or5000(s32 type) {
    if (type != 0) {
        mFlags.set(Flag::_1000);
        mFlags.set(Flag::_4000);
        stubbedLogFunction();
    } else {
        mFlags.set(Flag::_2000);
    }
}

void ResourceMgrTask::resetFlag20000() {
    mFlags.reset(Flag::_20000);
}

// NON_MATCHING: the original reloads handle->getUnit() (unused) after loading and stores the
// status to the stack only right before setStatusForResourceMgr_
bool ResourceMgrTask::doLoadOnThread(void* userdata) {
    auto* data = static_cast<ControlTaskData*>(userdata);
    Handle* handle = data->mResHandle;
    const sead::SafeString& path = data->mResLoadReq.mPath;
    if (res::returnFalse())
        stubbedLogFunction();

    const Handle::Status status = mCaches[getCacheIdx(path)]->loadResource(*data);

    if (res::returnFalse())
        stubbedLogFunction();
    handle->setStatusForResourceMgr_(status);
    return true;
}

void ResourceMgrTask::callCacheLoad2(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& context) {
    auto* data = static_cast<ControlTaskData*>(context.mUserData);
    Handle* handle = data->mResHandle;
    if (res::returnFalse())
        stubbedLogFunction();
    handle->mTaskHandle.finalize();
    result->setResult(false);
    if (res::returnFalse())
        stubbedLogFunction();
}

void ResourceMgrTask::loadTaskRemoveCb(const util::TaskRemoveCallbackContext& context) {
    auto* data = static_cast<ControlTaskData*>(context.mUserData);
    Handle* handle = data->mResHandle;
    if (res::returnFalse())
        stubbedLogFunction();
    handle->mTaskHandle.finalize();
    if (res::returnFalse())
        stubbedLogFunction();
}

void ResourceMgrTask::jamThreadMessageQueuesAndWait() {
    stubbedLogFunction();
    mResourceLoadingThread->resumeAndWaitForAck();
    mResourceMemoryThread->resumeAndWaitForAck();
    mResourceControlThread->resumeAndWaitForAck();
    mMovableMemoryThread->resumeAndWaitForAck();
    stubbedLogFunction();
}

bool ResourceMgrTask::sub_7101208400() const {
    if (auto* editor = KingEditor::instance(); editor && editor->get88() == 0)
        return false;
    return mFlags.isOn(Flag::_800);
}

bool ResourceMgrTask::isFlag4Set() const {
    return mFlags.isOn(Flag::_4);
}

void ResourceMgrTask::registerUnit(ResourceUnit* unit) {
    auto lock = sead::makeScopedLock(mUnitsCS);
    mUnits.pushBack(unit);
    if (res::returnFalse())
        stubbedLogFunction();
}

void ResourceMgrTask::deregisterUnit(ResourceUnit* unit) {
    auto lock = sead::makeScopedLock(mUnitsCS);
    if (unit->isLinkedToResourceMgr()) {
        mUnits.erase(unit);
        if (res::returnFalse())
            stubbedLogFunction();
    }
}

void ResourceMgrTask::requestUnload(Handle* handle) {
    auto* unit = handle->getUnit();
    if (!unit)
        return;

    unit->detachFromHandle_(handle);

    ControlTaskRequest req;
    req.mLaneId = u8(LaneId::_3);
    req.mHasHandle = false;
    req.mSynchronous = false;
    req.mThread = mResourceControlThread;
    req.mDelegate = &mUnitUnloadForSyncFn.fn;
    req.mUserData = unit;
    req.mPostRunCallback = &mUnitUnloadForSyncFn.cb;
    req.mName = "Unload";

    util::TaskMgrRequest task_mgr_request;
    task_mgr_request.request = &req;
    mResourceControlTaskMgr->submitRequest(task_mgr_request);
}

void ResourceMgrTask::requestUnloadForSync(Handle* handle) {
    auto* unit = handle->getUnit();
    if (!unit)
        return;

    if (mFlags.isOff(Flag::_4)) {
        sead::FormatFixedSafeString<256> message("↓↓↓\nファイル名 : %s\n↑↑↑\n", unit->getPath().cstr());
    }

    unit->detachFromHandle_(handle);

    ControlTaskRequest req;
    req.mLaneId = u8(LaneId::_3);
    req.mHasHandle = true;
    req.mSynchronous = true;
    req.mThread = mResourceControlThread;
    req.mDelegate = &mUnitUnloadForSyncFn.fn;
    req.mUserData = unit;
    req.mPostRunCallback = &mUnitUnloadForSyncFn.cb;
    req.mName = "Unload(ForSync)";

    util::TaskMgrRequest task_mgr_request;
    task_mgr_request.request = &req;
    mResourceControlTaskMgr->submitRequest(task_mgr_request);
}

void ResourceMgrTask::requestClearCache(ResourceUnit** p_unit, util::Task* task) {
    if (!p_unit || !*p_unit || !(*p_unit)->isStatusFlag8000Set()) {
        stubbedLogFunction();
        return;
    }

    if ((*p_unit)->getRefCount() > 0 || (*p_unit)->isStatus1() || (*p_unit)->isStatusFlag10000Set())
        return;

    (*p_unit)->setStatusFlag10000();

    {
        ControlTaskRequest req;
        req.mHasHandle = true;
        req.mSynchronous = false;
        req.mLaneId = u8(LaneId::_4);
        req.mThread = mResourceControlThread;
        req.mDelegate = &mUnitClearCacheForSyncFn.fn;
        req.mPostRunCallback = &mUnitClearCacheForSyncFn.cb;
        req.mUserData = *p_unit;
        req.mName = "ClearCache";
        if (task)
            task->submitRequest(req);
        else
            (*p_unit)->mTask3.submitRequest(req);
    }
    *p_unit = nullptr;
}

void ResourceMgrTask::requestClearCacheForSync(ResourceUnit** p_unit, bool clear_immediately,
                                               bool delete_immediately) {
    if (!p_unit || !*p_unit || !(*p_unit)->isStatusFlag8000Set()) {
        goto fail;
    }

    if ((*p_unit)->isStatus1() || !(*p_unit)->mCache || (*p_unit)->getRefCount() > 0)
        return;

    if ((*p_unit)->isStatusFlag10000Set()) {
    fail:
        stubbedLogFunction();
        return;
    }

    (*p_unit)->setStatusFlag10000();

    if (clear_immediately) {
        (*p_unit)->removeTask3FromQueue();
        (*p_unit)->clearCacheForSync(true);
        (*p_unit)->clearCache(nullptr);
        static_cast<void>((*p_unit)->getStatus());
        ResourceUnit* ptr = *p_unit;
        if (delete_immediately)
            deleteUnit(ptr, true);
        else
            requestDeleteUnit(&ptr);

    } else {
        ControlTaskRequest req;
        req.mHasHandle = true;
        req.mSynchronous = true;
        req.mLaneId = u8(LaneId::_4);
        req.mThread = mResourceControlThread;
        req.mDelegate = &mUnitClearCacheForSyncFn.fn;
        req.mUserData = *p_unit;
        req.mName = "ClearCache(ForSync)";
        (*p_unit)->mTask3.submitRequest(req);
    }
    *p_unit = nullptr;
}

#ifdef MATCHING_HACK_NX_CLANG
[[gnu::noinline]]
#endif
void ResourceMgrTask::deleteUnit(ResourceUnit*& unit, bool sync) {
    if (!unit)
        return;

    const bool immediate = mResourceControlThread->isPaused() || sync;
    if (!immediate && res::returnFalse())
        stubbedLogFunction();

    unit->unloadArchiveRes();

    if (immediate) {
        mUnitPool.freeForSync(unit);
        unit = nullptr;
    } else {
        mUnitPool.free(unit);
        unit = nullptr;
        if (res::returnFalse())
            stubbedLogFunction();
    }
}

void ResourceMgrTask::requestDeleteUnit(ResourceUnit** p_unit) {
    if (!p_unit || !*p_unit) {
        stubbedLogFunction();
        return;
    }

    if (mResourceControlThread->isPaused()) {
        if (res::returnFalse())
            stubbedLogFunction();

        deleteUnit(*p_unit, false);

    } else {
        ControlTaskRequest req;
        req.mHasHandle = false;
        req.mSynchronous = false;
        req.mLaneId = u8(LaneId::_5);
        req.mThread = mResourceControlThread;
        req.mDelegate = &mUnitDeleteFn;
        req.mName = "DeleteUnit";
        req.mUserData = *p_unit;
        (*p_unit)->mTask1.submitRequest(req);
    }

    *p_unit = nullptr;
}

bool ResourceMgrTask::canUseSdCard() const {
    return false;
}

bool ResourceMgrTask::isHostPath(const sead::SafeString&) const {
    return false;
}

bool ResourceMgrTask::sub_7101205F5C(void* unit) {
    return static_cast<ResourceUnit*>(unit)->initLoad();
}

void ResourceMgrTask::sub_7101205F64(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& context) {
    static_cast<ResourceUnit*>(context.mUserData)->requestPrepareLoad(result, context);
}

bool ResourceMgrTask::sub_7101205F7C(void* unit) {
    return static_cast<ResourceUnit*>(unit)->prepareLoad();
}

bool ResourceMgrTask::sub_7101205F84(void* unit) {
    return static_cast<ResourceUnit*>(unit)->sub_7101212F3C();
}

bool ResourceMgrTask::sub_7101205F8C(void* unit) {
    return static_cast<ResourceUnit*>(unit)->unloadForSync();
}

void ResourceMgrTask::sub_7101205F90(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& context) {
    static_cast<ResourceUnit*>(context.mUserData)->requestUnload(result, context);
}

bool ResourceMgrTask::sub_7101205FA8(void* unit) {
    return static_cast<ResourceUnit*>(unit)->unload(unit);
}

void ResourceMgrTask::sub_7101205FB0(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& context) {
    static_cast<ResourceUnit*>(context.mUserData)->postUnload(result, context);
}

bool ResourceMgrTask::sub_7101205FC8(void* unit) {
    return static_cast<ResourceUnit*>(unit)->clearCacheForSync(false);
}

void ResourceMgrTask::sub_7101205FD0(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& context) {
    static_cast<ResourceUnit*>(context.mUserData)->requestClearCache(result, context);
}

bool ResourceMgrTask::sub_7101205FE8(void* unit) {
    return static_cast<ResourceUnit*>(unit)->clearCache(unit);
}

void ResourceMgrTask::sub_7101205FF0(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& context) {
    static_cast<ResourceUnit*>(context.mUserData)->postClearCache(result, context);
}

bool ResourceMgrTask::sub_7101206008(void* unit_) {
    auto* unit = static_cast<ResourceUnit*>(unit_);
    ResourceMgrTask::instance()->deleteUnit(unit, false);
    return true;
}

bool ResourceMgrTask::sub_7101206A44(void* userdata) {
    mTexHandleMgr->xx();
    if (!sUnk_71026529C8) {
        auto* patrol = Patrol::instance();
        sUnk_71026529C8 = patrol ? patrol->mField0 : false;
    }
    return true;
}

void ResourceMgrTask::compactionThreadFunc(sead::Thread* thread,
                                           sead::MessageQueue::Element message) {
    if (message != 1)
        return;

    bool compacted;
    if (_9c0d3c == 0) {
        compacted = false;
    } else {
        compacted = mCompactedHeapMain->compact();
        if (mCompactedHeapMain->getState() == 3)
            _9c0d3c.exchange(0);
    }

    if (mCounter.isFlagSet() && _9c0d40 != 0) {
        compacted |= mCompactedHeapMip0->compact();
        if (mCompactedHeapMip0->getState() == 3)
            _9c0d40.exchange(0);
    }

    if (sUnk_71026529C8 && compacted) {
        mCompactedHeapMain->x("Main", true);
        if (mCounter.isFlagSet())
            mCompactedHeapMip0->x("Mip0", true);
    }
}

bool ResourceMgrTask::doClearAllCaches(void* userdata) {
    auto* data = static_cast<MemoryTaskData*>(userdata);

    if (returnFalse())
        stubbedLogFunction();

    auto lock = sead::makeScopedLock(mArenasCS);
    for (OverlayArena& arena : mArenas) {
        if (data->mStr.isEmpty()) {
            if (arena.isFlag1Set())
                stubbedLogFunction();
            else
                arena.clearCaches(-1, data->_8);
        } else if (arena.getHeap()->getName() == data->mStr) {
            arena.clearCaches(-1, data->_8);
        }
    }

    if (returnFalse())
        stubbedLogFunction();
    return true;
}

bool ResourceMgrTask::doClearCaches(void* userdata) {
    auto* data = static_cast<ClearCachesTaskData*>(userdata);

    if (returnFalse())
        stubbedLogFunction();

    auto lock = sead::makeScopedLock(mArenasCS);
    bool cleared = false;
    for (OverlayArena& arena : mArenas) {
        if (arena.isFlag1Set() && arena.clearCaches(data->_c, data->_8) > 0) {
            stubbedLogFunction();
            cleared = true;
            break;
        }
    }

    if (!cleared) {
        for (OverlayArena& arena : mArenas) {
            if (!arena.isFlag1Set() && arena.clearCaches(data->_c, data->_8) > 0) {
                stubbedLogFunction();
                break;
            }
        }
    }

    if (returnFalse())
        stubbedLogFunction();
    return true;
}

void ResourceMgrTask::sub_710120B118(util::DualHeap** heap, ResourceUnit* unit,
                                     OverlayArena* arena) {
    if (arena && *heap && arena->getHeap()->isInclude(*heap)) {
        arena->sub_71011FD4B8(heap, unit);
        *heap = nullptr;
    }
}

bool ResourceMgrTask::defragAllMemoryMgr(void* userdata) {
    sead::TickTime start;
    stubbedLogFunction();

    constexpr size_t buffer_size = 0x1e00000;
    auto* tex_arena = mTexHandleMgr->getArchiveWork()->getArena();
    auto* buffer = new (tex_arena->getHeap(), -8, std::nothrow) u8[buffer_size];
    if (!buffer)
        mTexHandleMgr->getArchiveWork()->getArena()->destroy();

    {
        auto lock = sead::makeScopedLock(mArenasCS);
        _4c8 = 0;
        for (auto& arena : mArenas) {
            if (!arena.isFlag1Set())
                _4c8 += arena.getNumUnits();
        }
    }

    for (auto& arena : mArenas) {
        if (arena.isFlag1Set())
            stubbedLogFunction();
        else
            arena.sub_71011FD868(buffer, buffer_size, &_4cc);
    }

    {
        sead::ScopedCurrentHeapSetter setter(mTexHandleMgr->getArchiveWork()->getArena()->getHeap());
        delete[] buffer;
    }

    stubbedLogFunction();
    mMovableMemoryThread->getTaskQueue()->unblockTasks(u8(LaneId::_6));
    mMovableMemoryThread->getTaskQueue()->unblockTasks(u8(LaneId::_3));
    mMovableMemoryThread->getTaskQueue()->unblockTasks(u8(LaneId::_2));
    mMovableMemoryThread->getTaskQueue()->unblockTasks(u8(LaneId::_1));
    mMovableMemoryThread->getTaskQueue()->unblockTasks(u8(LaneId::_0));
    return true;
}

bool ResourceMgrTask::calcOverlayArenaHeapSize(void* userdata) {
    auto lock = sead::makeScopedLock(mCritSection4);
    auto arenas_lock = sead::makeScopedLock(mArenasCS);

    const OverlayArena::HeapSizeArg arg = mHeapSizeArg;
    auto* arena = mArenas.nth(mArenaIdx);
    if (!arena)
        return false;

    arena->sub_71011FDC20(arg);
    mTickTime.setNow();
    mArenaIdx = (mArenaIdx + 1) % mArenas.size();
    return true;
}

bool ResourceMgrTask::calc_(void*) {
    if (mCacheControlFlags.testAndClear(CacheControlFlag::ClearAllCachesRequested)) {
        MemoryTaskRequest req;
        req.mLaneId = u8(LaneId::_9);
        req.mHasHandle = true;
        req.mSynchronous = true;
        req.mThread = mResourceMemoryThread;
        req.mDelegate = &mClearAllCachesFn;
        req.mName = "ClearAllCaches";
        req.mData_8 = false;
        req.mData_c = -1;

        util::TaskMgrRequest request;
        request.request = &req;
        mResourceMemoryTaskMgr->submitRequest(request);
        mTexHandleMgr->clearAllCache();
        stubbedLogFunction();
    }
    clearUnits_();
    return true;
}

bool ResourceMgrTask::callSystemCalc_(void* userdata) {
    systemCalc_();
    return true;
}

// NON_MATCHING: loop shape differs (index arithmetic of the backwards search for '.')
void ResourceMgrTask::addSExtensionPrefix(sead::StringBuilder& builder) const {
    const s32 length = builder.getLength();
    s32 ext_idx = length;
    for (; ext_idx > 0; --ext_idx) {
        if (builder.cstr()[ext_idx - 1] == '.')
            break;
    }

    if (ext_idx == 0)
        return;

    sead::FixedStringBuilder<32> extension;
    extension.copy(&builder[ext_idx]);

    const sead::SafeString extension_str = extension.cstr();
    if (mExtensions2.binarySearch(&extension_str) == -1)
        return;

    builder.copyAtWithTerminate(ext_idx, "s", 1);
    builder.copyAtWithTerminate(ext_idx + 1, extension.cstr(), extension.getLength());
}

// NON_MATCHING: the backwards extension search has a different loop shape.
void ResourceMgrTask::removeSExtensionPrefix(sead::StringBuilder& builder) {
    const s32 length = builder.getLength();
    s32 ext_idx = length;
    for (; ext_idx > 0; --ext_idx) {
        if (builder.cstr()[ext_idx - 1] == '.')
            break;
    }
    if (ext_idx == 0)
        return;

    sead::FixedStringBuilder<16> extension;
    extension.append(&sead::SafeString(&builder[ext_idx]).at(1), -1);
    const sead::SafeString extension_str = extension.cstr();
    if (mExtensions2.binarySearch(&extension_str) != -1)
        builder.copyAtWithTerminate(ext_idx, extension.cstr(), extension.getLength());
}

bool ResourceMgrTask::dropSFromExtensionIfNeeded(const sead::SafeString& path,
                                                 sead::BufferedSafeString& new_path, s32 dot_idx,
                                                 const sead::SafeString& extension) const {
    if (extension == "sbfevfl" || extension == "sbcamanim" || extension == "sbarslist") {
        new_path.copyAtWithTerminate(0, path, dot_idx);
        new_path.appendWithFormat(".%s", &extension.at(1));
        return true;
    }
    return mExtensions2.binarySearch(&extension) != -1;
}

void ResourceMgrTask::unloadSeadResource(sead::Resource* resource) {
    if (res::returnFalse())
        stubbedLogFunction();

    sead::ResourceMgr::instance()->unload(resource);
    stubbedLogFunction();

    if (res::returnFalse())
        stubbedLogFunction();
}

u32 ResourceMgrTask::getResourceSize(const sead::SafeString& name, void* userdata) const {
    if (!userdata)
        return mResourceInfoContainer.getResourceSize(name);

    mFileDevicePrefixesLock.readLock();

    for (const auto& entry : mFileDevicePrefixes) {
        if (entry.getUserData() == userdata) {
            const u32 size = mResourceInfoContainer.getResourceSize(entry.getPrefix(), name);
            if (size == 0 && entry.getField28())
                break;

            mFileDevicePrefixesLock.readUnlock();
            return size;
        }
    }

    mFileDevicePrefixesLock.readUnlock();
    return mResourceInfoContainer.getResourceSize(name);
}

void ResourceMgrTask::registerFileDevicePrefix(FileDevicePrefix& prefix) {
    mFileDevicePrefixesLock.writeLock();
    mFileDevicePrefixes.pushBack(&prefix);
    mFileDevicePrefixesLock.writeUnlock();
}

void ResourceMgrTask::deregisterFileDevicePrefix(FileDevicePrefix& prefix) {
    mFileDevicePrefixesLock.writeLock();
    mFileDevicePrefixes.erase(&prefix);
    mFileDevicePrefixesLock.writeUnlock();
}

void ResourceMgrTask::callStubbedFunctionOnArenas() {
    auto lock = sead::makeScopedLock(mArenasCS);
    for (OverlayArena& arena : mArenas) {
        if (arena.isFlag8Set())
            arena.stubbed();
    }
}

void ResourceMgrTask::updateResourceArenasFlag8() {
    mArenaForResourceS.updateFlag8(false);
    mArenaForResourceL.updateFlag8(false);
}

// NON_MATCHING: branching
sead::Heap* ResourceMgrTask::makeHeapForUnit(const MakeHeapArg& arg) {
    const auto heap_size = arg.heap_size;
    const auto path = arg.path;

    OverlayArena* arena = arg.arena;
    if (!arena) {
        if (heap_size > 0x80000)
            arena = &mArenaForResourceL;
        else
            arena = &mArenaForResourceS;
    }

    sead::Heap* const heap =
        arena->makeDualHeap(heap_size, path, sead::Heap::cHeapDirection_Forward, arg.unit, false);

    if (!heap) {
        static_cast<void>(arena->isFlag10Set());
        *arg.out_arena1 = arena;
        return nullptr;
    }

    if (arg.out_arena2 == nullptr)
        return heap;

    *arg.out_arena1 = arena;
    *arg.out_arena2 = arena;
    return heap;
}

ResourceUnit* ResourceMgrTask::clearCachesAndGetUnit(const GetUnitArg& arg) {
    auto* unit = mUnitPool.tryAlloc();

    if (!unit) {
        util::TaskQueueLock lock;

        auto* queue = mResourceControlThread->getTaskQueue();
        auto it = queue->activeTasksRobustBegin(&lock);
        const auto end = queue->activeTasksRobustEnd();

        while (it != end && it->getLaneId() >= u8(ResourceMgrTask::LaneId::_5)) {
            it->removeFromQueue2();
            it->processOnCurrentThreadDirectly(mResourceControlThread);
            ++it;
        }

        unit = mUnitPool.tryAlloc();
    }

    if (!unit) {
        ClearCachesTaskData data;
        data._8 = true;
        data._c = 100;
        util::TaskRequest req;
        req.mLaneId = u8(LaneId::_8);
        req.mHasHandle = true;
        req.mSynchronous = true;
        req.mThread = mResourceMemoryThread;
        req.mDelegate = &mClearCachesFn;
        req.mUserData = &data;
        req.mName = "ClearCaches";
        mTask3->submitRequest(req);

        unit = mUnitPool.tryAlloc();
    }

    if (!unit) {
        util::TaskQueueLock lock;

        auto* queue = mResourceControlThread->getTaskQueue();
        auto it = queue->activeTasksRobustBegin(&lock);
        const auto end = queue->activeTasksRobustEnd();

        while (it != end && it->getLaneId() >= u8(ResourceMgrTask::LaneId::_5)) {
            it->removeFromQueue2();
            it->processOnCurrentThreadDirectly(mResourceControlThread);
            ++it;
        }

        unit = mUnitPool.alloc();
    }

    if (!unit->init(*arg.unit_init_arg))
        return nullptr;

    return unit;
}

void ResourceMgrTask::setActorCreateInitializerThreads(
    const SetActorCreateInitializerThreadsArg& arg) {
    mFlags.set(Flag::_8);
    mActorCreateInitializerThreads = arg.threads;
    stubbedLogFunction();
}

void ResourceMgrTask::clearActorCreateInitializerThreads() {
    mFlags.reset(Flag::_8);
    mActorCreateInitializerThreads = nullptr;
    stubbedLogFunction();
}

void ResourceMgrTask::pauseThreads() {
    stubbedLogFunction();
    mMovableMemoryThread->pauseAndWaitForAck();
    mMovableMemoryThread->cancelTasks(3);
    mResourceControlThread->pauseAndWaitForAck();
    mResourceMemoryThread->pauseAndWaitForAck();
    mResourceLoadingThread->pauseAndWaitForAck();
    stubbedLogFunction();
}

void ResourceMgrTask::resumeThreads() {
    stubbedLogFunction();
    mResourceLoadingThread->resume();
    mResourceMemoryThread->resume();
    mResourceControlThread->resume();
    mMovableMemoryThread->resume();
}

sead::ParallelSZSDecompressor* ResourceMgrTask::getSzsDecompressor() {
    mSzsDecompressorCS.lock();
    sead::ParallelSZSDecompressor* ptr = nullptr;
    OverlayArenaSystem::instance()->getSzsDecompressor(&ptr);
    return ptr;
}

void ResourceMgrTask::unlockSzsDecompressorCS() {
    mSzsDecompressorCS.unlock();
}

bool ResourceMgrTask::getUncompressedSize(u32* size, const sead::SafeString& path,
                                          sead::FileDevice* device) const {
    auto lock = sead::makeScopedLock(mSzsDecompressorCS);

    if (!device)
        device = mSeadMainFileDevice;

    sead::FileHandle handle;
    if (!device->tryOpen(&handle, path, sead::FileDevice::cFileOpenFlag_ReadOnly)) {
        stubbedLogFunction();
        return false;
    }

    u32 read_size = 0;
    handle.tryRead(&read_size, mOffsetReadBuf, 0x10);
    *size = sead::Mathu::roundUpPow2(sead::SZSDecompressor::getDecompSize(mOffsetReadBuf), 32);
    return true;
}

void ResourceMgrTask::clearUnits_() {
    const auto lock = sead::makeScopedLock(mUnitsCS);

    const int num_units = mUnits.size();
    if (num_units != 0 && returnFalse())
        stubbedLogFunction();

    for (auto& unit_ref : mUnits.robustRange()) {
        ResourceUnit* unit = &unit_ref;
        if (unit->mTask3.canSubmitRequest()) {
            mUnits.erase(unit);
            requestClearCache(&unit);
        }
    }

    if (mUnits.size() != 0 || (num_units != 0 && returnFalse()))
        stubbedLogFunction();
}

void ResourceMgrTask::systemCalc_() {
    if (mTask1->canSubmitRequest()) {
        util::TaskRequest request;
        request.mSynchronous = false;
        request.mHasHandle = false;
        request.mLaneId = u8(LaneId::_6);
        request.mThread = mResourceControlThread;
        request.mName = "res::System::calc";
        mTask1->submitRequest(request);
    }

    mTexHandleMgr->preCalc();
    updateCompaction();
    mTexHandleMgr->calc();
}

// NON_MATCHING: reordering
void ResourceMgrTask::setCompactionStopped(bool stopped) {
    u32 old_counter;
    if (stopped)
        old_counter = mCompactionCounter.decrement();
    else
        old_counter = mCompactionCounter.increment();

    stubbedLogFunction();
    if (mCompactionCounter == 0)
        stubbedLogFunction();
    else if (old_counter == 0)
        stubbedLogFunction();
}

void ResourceMgrTask::x(bool b) {
    if (mTexHandleMgr)
        mTexHandleMgr->sub_7100FE60B0(b);
}

void ResourceMgrTask::x_0() {
    mTexHandleMgr->sub_7100FE5190();
    mCounter.reset();

    if (mCompactedHeapMip0) {
        mCompactedHeapMain->setBuffer(nullptr, 0);
        mCompactedHeapMip0->setBuffer(nullptr, 0);
        mCompactedHeapMip0->destroy();
        mCompactedHeapMip0 = nullptr;
        util::safeDeleteArray(mCompactedHeapMip0Buffer);
        util::safeDeleteArray(mCompactedHeapMainBuffer2);
    }
}

void ResourceMgrTask::auto12() {
    mTexHandleMgr->sub_7100FE5334();
}

void ResourceMgrTask::sub_7101206D64() {
    mTexHandleMgr->sub_7100FE53BC();
}

void ResourceMgrTask::x_1(bool b) {
    if (mTexHandleMgr)
        mTexHandleMgr->sub_7100FE60DC(b);
}

void ResourceMgrTask::repairAllHandlesForSync() {
    if (mTexHandleMgr)
        mTexHandleMgr->repairAllHandlesForSync();
}

bool ResourceMgrTask::x_2() {
    return mTexHandleMgr->sub_7100FE6120();
}

bool ResourceMgrTask::isCompactionStopped() const {
    return mCompactionCounter == 0;
}

void ResourceMgrTask::registerBfRes(BfRes* res) {
    mBfResList.pushBack(res);
}

void ResourceMgrTask::updateCompaction() {
    auto lock = sead::makeScopedLock(mCritSection3);

    if (mCounter.isFlagSet()) {
        if (mCompactionCounter == 0) {
            _9c0d3c.exchange(1);
            _9c0d40.exchange(1);
        }

        if (_9c0d3c != 0 || _9c0d40 != 0) {
            if (mCompactedHeapMain)
                mCompactedHeapMain->incrementCompactionCount();
            if (mCompactedHeapMip0)
                mCompactedHeapMip0->incrementCompactionCount();
            mCompactionThread->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
        }
    }

    mTexHandleMgr->d();
    mTexHandleList->sub_71012BD6BC();
    for (BfRes& res : mBfResList)
        res.sub_71011FFECC();
    mBfResList.clear();
}

void ResourceMgrTask::requestCalc() {
    frm::WorkerSupportThreadMgr::instance()->submitRequest(2, &mSystemCalcFn);
}

void ResourceMgrTask::waitForCalc() {
    frm::WorkerSupportThreadMgr::instance()->waitForTask(2);
}

bool ResourceMgrTask::initTempResourceLoader(TempResourceLoader* loader,
                                             TempResourceLoader::InitArg& arg) {
    arg.work = mTexHandleMgr->getArchiveWork();
    return loader->init(arg);
}

bool ResourceMgrTask::returnTrue1() {
    return true;
}

bool ResourceMgrTask::isOutOfMemory() {
    if (mFlags.isOn(Flag::_1000)) {
        mFlags.reset(Flag::_1000);
        return true;
    }

    {
        auto lock = sead::makeScopedLock(mArenasCS);
        for (OverlayArena& arena : mArenas) {
            if (arena.checkIsOom())
                return true;
        }
    }

    if (mTexHandleMgr && mTexHandleMgr->isTooSlow(60)) {
        if (PlayReportMgr::instance() && PlayReportMgr::instance()->getReporter())
            PlayReportMgr::instance()->getReporter()->addPanicReason(PanicReason::TextureHandleMgrSlow);
        return true;
    }
    return false;
}

void ResourceMgrTask::x_4() {
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_5));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_4));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_3));

    MemoryTaskRequest req;
    req.mLaneId = u8(LaneId::_9);
    req.mHasHandle = true;
    req.mSynchronous = true;
    req.mThread = mResourceMemoryThread;
    req.mDelegate = &mClearAllCachesFn;
    req.mName = "ClearAllCaches";
    req.mData_8 = false;
    req.mData_c = -1;

    util::TaskMgrRequest task_mgr_request;
    task_mgr_request.request = &req;
    mResourceMemoryTaskMgr->submitRequest(task_mgr_request);
    mTexHandleMgr->clearAllCache();
}

void ResourceMgrTask::x_5() {
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_5));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_4));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_3));

    MemoryTaskRequest req;
    req.mLaneId = u8(LaneId::_9);
    req.mHasHandle = true;
    req.mSynchronous = true;
    req.mThread = mResourceMemoryThread;
    req.mDelegate = &mClearAllCachesFn;
    req.mName = "ClearAllCaches";
    req.mData_8 = false;
    req.mData_c = -1;

    util::TaskMgrRequest task_mgr_request;
    task_mgr_request.request = &req;
    mResourceMemoryTaskMgr->submitRequest(task_mgr_request);
}

void ResourceMgrTask::x_6() {
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_5));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_4));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_3));

    MemoryTaskRequest req;
    req.mLaneId = u8(LaneId::_9);
    req.mHasHandle = true;
    req.mSynchronous = false;
    req.mThread = mResourceMemoryThread;
    req.mDelegate = &mClearAllCachesFn;
    req.mName = "ClearAllCaches";
    req.mData_8 = false;
    req.mData_c = -1;

    util::TaskMgrRequest task_mgr_request;
    task_mgr_request.request = &req;
    mResourceMemoryTaskMgr->submitRequest(task_mgr_request);
}

void ResourceMgrTask::clearCacheWithFileExtension(const sead::SafeString& extension) {
    stubbedLogFunction();
    const s32 idx = getCacheIdx(extension);
    stubbedLogFunction();
    mCaches[idx]->eraseUnits();
}

void ResourceMgrTask::clearAllCachesSynchronously(OverlayArena* arena) {
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_5));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_4));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_3));

    MemoryTaskRequest req;
    req.mLaneId = u8(LaneId::_9);
    req.mHasHandle = true;
    req.mSynchronous = true;
    req.mThread = mResourceMemoryThread;
    req.mDelegate = &mClearAllCachesFn;
    req.mName = "ClearAllCaches";
    req.mData_8 = false;
    req.mData_c = -1;
    req.mData_mStr = arena->getHeap()->getName();

    util::TaskMgrRequest task_mgr_request;
    task_mgr_request.request = &req;
    mResourceMemoryTaskMgr->submitRequest(task_mgr_request);
}

void ResourceMgrTask::requestDefragAllMemoryMgr() {
    clearUnits_();

    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_5));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_4));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_3));

    if (!mTask2->canSubmitRequest()) {
        stubbedLogFunction();
        return;
    }

    _4c8 = -1;
    _4cc = 0;

    mMovableMemoryThread->getTaskQueue()->blockTasksAndReloadThreads(u8(LaneId::_0));
    mMovableMemoryThread->getTaskQueue()->blockTasksAndReloadThreads(u8(LaneId::_1));
    mMovableMemoryThread->getTaskQueue()->blockTasksAndReloadThreads(u8(LaneId::_2));
    mMovableMemoryThread->getTaskQueue()->blockTasksAndReloadThreads(u8(LaneId::_3));
    mMovableMemoryThread->getTaskQueue()->blockTasksAndReloadThreads(u8(LaneId::_6));
    mMovableMemoryThread->getTaskQueue()->cancelTasks(u8(LaneId::_0));
    mMovableMemoryThread->getTaskQueue()->cancelTasks(u8(LaneId::_1));
    mMovableMemoryThread->getTaskQueue()->cancelTasks(u8(LaneId::_2));
    mMovableMemoryThread->getTaskQueue()->cancelTasks(u8(LaneId::_3));
    mMovableMemoryThread->getTaskQueue()->cancelTasks(u8(LaneId::_6));

    auto* arena = mTexHandleMgr->getArchiveWork()->getArena();

    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_5));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_4));
    mResourceControlThread->getTaskQueue()->waitForLaneToEmpty(u8(LaneId::_3));

    {
        MemoryTaskRequest req;
        req.mLaneId = u8(LaneId::_9);
        req.mHasHandle = true;
        req.mSynchronous = false;
        req.mThread = mResourceMemoryThread;
        req.mDelegate = &mClearAllCachesFn;
        req.mName = "ClearAllCaches";
        req.mData_8 = false;
        req.mData_c = -1;
        req.mData_mStr = arena->getHeap()->getName();

        util::TaskMgrRequest task_mgr_request;
        task_mgr_request.request = &req;
        mResourceMemoryTaskMgr->submitRequest(task_mgr_request);
    }

    {
        ControlTaskRequest req;
        req.mLaneId = u8(LaneId::_7);
        req.mHasHandle = true;
        req.mSynchronous = false;
        req.mThread = mResourceMemoryThread;
        req.mDelegate = &mDefragAllMemoryMgrFn;
        req.mUserData = nullptr;
        req.mName = "DefragAllMemoryMgr";
        mTask2->submitRequest(req);
    }
}

bool ResourceMgrTask::returnTrue() {
    return true;
}

bool ResourceMgrTask::returnTrue2() {
    return true;
}

void ResourceMgrTask::removeOverlayArena(OverlayArena* arena) {
    mTask.removeFromQueue();

    auto lock = sead::makeScopedLock(mArenasCS);
    mArenaIdx = 0;
    if (mArenas.isNodeLinked(arena)) {
        mArenas.erase(arena);
        stubbedLogFunction();
    }
}

void ResourceMgrTask::setPack(Handle* pack) {
    mPackHandle = pack;
    res::stubbedLogFunction();
}

}  // namespace ksys::res
