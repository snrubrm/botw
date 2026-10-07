#include "KingSystem/Resource/resUnit.h"
#include <filedevice/seadArchiveFileDevice.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <resource/seadParallelSZSDecompressor.h>
#include <filedevice/seadPath.h>
#include <resource/seadArchiveRes.h>
#include <resource/seadResourceMgr.h>
#include <thread/seadThread.h>
#include <time/seadTickSpan.h>
#include "KingSystem/Resource/resCache.h"
#include "KingSystem/Resource/resCacheCriticalSection.h"
#include "KingSystem/Resource/resControlTask.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resOffsetReadFileDevice.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

ResourceUnit::ResourceUnit(const InitArg& arg)
    : mArena(arg.arena), mLoadReqArena(arg.load_req->mArena), mLoadReqField68(arg.load_req->_68),
      mCache(arg.cache), mFileDevice(arg.load_req->mFileDevice),
      mLoadReqAllocSize(arg.load_req->_34), mAllocSize(arg.alloc_size), mPath(arg.path),
      mHeap(arg.heap) {
    init(arg);
}

ResourceUnit::ResourceUnit() = default;

bool ResourceUnit::init(const ResourceUnit::InitArg& arg) {
    mCacheFlags.makeAllZero();
    mFlags.makeAllZero();
    mStatusFlags.makeAllZero();
    mStatus = Status::_0;
    mArena = arg.arena;
    mArena1 = nullptr;
    mArena2 = nullptr;
    mLoadReqArena = arg.load_req->mArena;
    mArchiveRes = nullptr;
    mResource = nullptr;
    mLoadReqField68 = arg.load_req->_68;
    mCache = arg.cache;
    mFileDevice = arg.load_req->mFileDevice;
    mLoadReqAllocSize = arg.load_req->_34;
    mAllocSize = arg.alloc_size;
    mInfoAllocSize = 0;
    mRefCount.storeNonAtomic(0);
    mCounter.storeNonAtomic(0);
    mEvent.resetSignal();
    mLoadArg = {};
    mPath = arg.path;
    mHeap = arg.heap;

    if (arg.load_req->mPackHandle) {
        SimplePackedLoadRequest request;
        request._8 = true;
        request.mRequester = "ResourceUnit";
        request.mLaneId = 2;
        request.mPack = arg.load_req->mPackHandle;
        mArchiveRes = sead::DynamicCast<sead::ArchiveRes>(mArchiveResHandle.load("", &request));
    }

    mMapNode.key().setKey(mPath);

    mLoadArg.path = mPath;
    mLoadArg.instance_heap = nullptr;
    mLoadArg.instance_alignment = sizeof(void*);
    mLoadArg.load_data_heap = nullptr;
    mLoadArg.load_data_alignment = arg.load_req->mLoadDataAlignment;
    mLoadArg.load_data_buffer = nullptr;
    mLoadArg.load_data_buffer_size = arg.load_req->mBufferSize;
    mLoadArg.factory = arg.load_req->mEntryFactory;
    mLoadArg.device = arg.load_req->mAocFileDevice;
    mLoadArg.assert_on_alloc_fail = false;

    bool load_from_archive;
    if (sead::IsDerivedFrom<sead::ArchiveFileDevice>(mLoadArg.device))
        load_from_archive = true;
    else
        load_from_archive = arg.load_req->mPackHandle != nullptr;

    mStatusFlags.change(StatusFlag::BufferSizeIsNonZero, arg.load_req->mBufferSize != 0);
    mStatusFlags.change(StatusFlag::LoadFromArchive, load_from_archive);
    mStatusFlags.change(StatusFlag::LoadReqField24IsTrue, arg.load_req->_24);

    mFlags.change(Flag::_1, arg.set_flag_1);
    mFlags.change(Flag::_2, arg.set_flag_2);
    mFlags.change(Flag::_4, arg.set_flag_4);

#ifdef MATCHING_HACK_NX_CLANG
    mStatusFlags.change(StatusFlag::_20000,
                        arg.load_req_field_26 &&
                            !*static_cast<const volatile bool*>(&arg.load_req_field_28));
#else
    mStatusFlags.change(StatusFlag::_20000, arg.load_req_field_26 && !arg.load_req_field_28);
#endif
    mStatusFlags.change(StatusFlag::_40000, arg.load_req->_27);
    mStatusFlags.change(StatusFlag::HasHeap, arg.heap != nullptr);
    mStatusFlags.change(StatusFlag::_80000, arg.load_req_field_28);

    if (arg.handle) {
        arg.handle->setUnit(this);
        mRefCount.increment();
        mStatusFlags.reset(StatusFlag::NeedToIncrementRefCount);
    }

    {
        util::TaskDelegateSetter setter;
        mTask1.setDelegate(setter);
    }

    {
        util::TaskDelegateSetter setter;
        mTask2.setDelegate(setter);
    }

    if (mStatusFlags.isOn(StatusFlag::_80000)) {
        mRefCount.increment();
        mStatusFlags.reset(StatusFlag::NeedToIncrementRefCount);
        stubbedLogFunction();
    }

    return true;
}

ResourceUnit::~ResourceUnit() {
    unloadArchiveRes();
}

void ResourceUnit::unloadArchiveRes() {
    if (mArchiveRes) {
        mArchiveRes = nullptr;
        mArchiveResHandle.requestUnload();
    }
}

void ResourceUnit::attachHandle(Handle* handle) {
    handle->setUnit(this);
    mRefCount.increment();
    mStatusFlags.reset(StatusFlag::NeedToIncrementRefCount);
}

s32 ResourceUnit::getRefCount() const {
    return mRefCount;
}

ResourceUnit::Status ResourceUnit::getStatus() const {
    return mStatus;
}

static const ResourceUnit::Status sUnitStatusTransitionTable[] = {
    ResourceUnit::Status::_8,  ResourceUnit::Status::_11, ResourceUnit::Status::_11,
    ResourceUnit::Status::_14, ResourceUnit::Status::_14,
};

// NON_MATCHING: ldr + sxtw -> ldrsw
void ResourceUnit::updateStatus() {
    const s32 idx = mStatus;
    if (Status::_2 <= idx && idx <= Status::_6)
        mStatus = sUnitStatusTransitionTable[idx];
}

bool ResourceUnit::isTask1NotQueued() const {
    return mTask1.getStatus() == util::Task::Status::RemovedFromQueue;
}

bool ResourceUnit::isStatus0() const {
    return mStatus == Status::_0;
}

bool ResourceUnit::isTask1ActiveOrStatus7() const {
    if (!mTask1.isInactive())
        return true;
    if (isTask1NotQueued())
        return false;
    return mStatus == Status::_7;
}

bool ResourceUnit::isStatus1() const {
    return mStatus == Status::_1;
}

bool ResourceUnit::needsParse() const {
    auto* res = sead::DynamicCast<Resource>(mResource);
    if (mStatus != Status::_8 && mStatus != Status::_11)
        return false;
    return res && res->needsParse();
}

bool ResourceUnit::isStatus9_12_15() const {
    return mStatus == Status::_9 || mStatus == Status::_12 || mStatus == Status::_15;
}

// NON_MATCHING: branching for the second if
bool ResourceUnit::isParseOk() const {
    auto* ksys_res = sead::DynamicCast<res::Resource>(mResource);

    const auto status = mStatus.value();

    if (status == Status::_14)
        return true;

    if (status == Status::_8 && !ksys_res)
        return mResource != nullptr;

    if (status == Status::_8 && ksys_res)
        return !ksys_res->needsParse();

    return false;
}

bool ResourceUnit::isStatusFlag8000Set() const {
    return mStatusFlags.isOn(StatusFlag::NeedToIncrementRefCount);
}

bool ResourceUnit::isLinkedToResourceMgr() const {
    return mResMgrUnitListNode.isLinked();
}

size_t ResourceUnit::getHeapSize() const {
    return mHeap ? mHeap->getSize() : 0;
}

sead::Heap* ResourceUnit::getHeap() const {
    return mHeap;
}

bool ResourceUnit::isLinkedToCache() const {
    return mCacheFlags.isOn(CacheFlag::IsLinkedToCache);
}

void ResourceUnit::setIsLinkedToCache(bool linked) {
    mCacheFlags.change(CacheFlag::IsLinkedToCache, linked);
    if (returnFalse())
        stubbedLogFunction();
}

void ResourceUnit::removeFromCache() {
    if (mCache)
        mCache->eraseUnit(this);
    else
        stubbedLogFunction();
}

bool ResourceUnit::removeTask3FromQueue() {
    mTask3.removeFromQueue();
    return true;
}

void ResourceUnit::requestInitLoad(const RequestInitLoadArg& arg) {
    mStatus = Status::_7;

    util::TaskRequest req;
    req.mHasHandle = arg.has_handle;
    req.mSynchronous = false;
    req.mLaneId = arg.lane_id;
    req.mThread = ResourceMgrTask::instance()->getResourceMemoryThread();
    req.mDelegate = &ResourceMgrTask::instance()->getUnitInitLoadFn().fn;
    req.mUserData = this;
    req.mPostRunCallback = &ResourceMgrTask::instance()->getUnitInitLoadFn().cb;
    req.mName = mPath;
    mTask1.submitRequest(req);

    if (returnFalse2(sead::SafeString(mPath)))
        stubbedLogFunction();
}

bool ResourceUnit::waitForResourceAndParse(Context* context) {
    const auto adjust_heap_and_dec_ref = [&] {
        adjustHeapAndArena();
        if (mStatusFlags.isOn(StatusFlag::_80000)) {
            mRefCount.decrement();
            mStatusFlags.reset(StatusFlag::_80000);
            ksys::res::stubbedLogFunction();
        }
    };

    if (isParseOk())
        return true;

    if (mCounter.increment() >= 1) {
        mEvent.wait();
        if (mStatus != Status::_15 && mStatus != Status::_12)
            return true;
        ksys::res::stubbedLogFunction();
        return false;
    }

    mTask1.wait();
    bool set_status_12 = true;
    if (mResource) {
        auto* res = sead::DynamicCast<ksys::res::Resource>(mResource);
        if (!res || !res->needsParse()) {
            mEvent.setSignal();
            return true;
        }

        bool finish_parsing = mStatus != Status::_8;
        if (!finish_parsing) {
            auto* heap = mHeap;
            mStatus = Status::_10;
            if (context)
                res->setContext(context);

            if (res->parse(context, heap)) {
                mStatus = Status::_11;
                finish_parsing = true;
            } else {
                adjust_heap_and_dec_ref();
            }
        }

        if (finish_parsing) {
            mStatus = Status::_13;
            if (mResource) {
                bool ok = true;
                if (auto* ksys_res = sead::DynamicCast<ksys::res::Resource>(mResource)) {
                    if (context)
                        ksys_res->setContext(context);
                    ok = ksys_res->finishParsing(context);
                }
                mStatus = ok ? Status::_14 : Status::_15;
                if (ok) {
                    adjustHeapAndArena();
                    mEvent.setSignal();
                    return true;
                }
            }
            adjust_heap_and_dec_ref();
            set_status_12 = false;
        }
    }

    if (set_status_12)
        mStatus = Status::_12;

    mEvent.setSignal();

    ksys::res::stubbedLogFunction();
    return false;
}

bool ResourceUnit::waitForTask1() {
    mTask1.wait();
    return true;
}

void ResourceUnit::adjustHeapAndArena() {
    if (mStatusFlags.isOn(StatusFlag::HasHeap)) {
        mStatusFlags.set(StatusFlag::_8);
        return;
    }

    if (mStatusFlags.isOn(StatusFlag::_8)) {
        auto* arena = mArena1;

        if (mStatusFlags.isOff(StatusFlag::_2)) {
            arena->addSize(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_2);
        }

        if (mStatusFlags.isOff(StatusFlag::_4) &&
            mStatusFlags.isOff(StatusFlag::NeedToIncrementRefCount)) {
            arena->addSize2(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_4);
            return;
        }

    } else {
        if (mStatusFlags.isOn(StatusFlag::_40000)) {
            ControlTaskRequest req{false};
            req.mHasHandle = false;
            req.mSynchronous = false;
            req.mLaneId = u8(res::ResourceMgrTask::LaneId::_10);
            req.mThread = res::ResourceMgrTask::instance()->getResourceMemoryThread();
            req.mDelegate = &res::ResourceMgrTask::instance()->getUnitAdjustHeapFn();
            req.mUserData = this;
            req.mName = "HeapAdjust";
            mTask2.submitRequest(req);
            return;
        }

        auto* arena = mArena1;

        if (mStatusFlags.isOff(StatusFlag::_2)) {
            arena->addSize(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_2);
        }

        if (mStatusFlags.isOff(StatusFlag::_4) &&
            mStatusFlags.isOff(StatusFlag::NeedToIncrementRefCount)) {
            arena->addSize2(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_4);
            return;
        }
    }
}

bool ResourceUnit::clearCacheForSync(bool x) {
    lockCacheCriticalSection();
    if (returnFalse())
        stubbedLogFunction();

    if (mRefCount > 0) {
        stubbedLogFunction();
        return false;
    }

    removeFromCache();
    if (returnFalse())
        stubbedLogFunction();

    unlockCacheCriticalSection();
    return true;
}

bool ResourceUnit::waitForTask1(const sead::TickSpan& span) {
    return mTask1.wait(span);
}

void ResourceUnit::detachFromHandle_(Handle* handle) {
    handle->setUnit(nullptr);
}

void ResourceUnit::setStatusFlag10000() {
    mStatusFlags.set(StatusFlag::_10000);
}

bool ResourceUnit::isStatusFlag10000Set() const {
    return mStatusFlags.isOn(StatusFlag::_10000);
}

bool ResourceUnit::sub_7101212F3C(void*) {
    if (mHeap) {
        mHeap->adjust();
        mStatusFlags.set(StatusFlag::_8);
        auto* arena = mArena1;

        if (mStatusFlags.isOff(StatusFlag::_2)) {
            arena->addSize(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_2);
        }

        if (mStatusFlags.isOff(StatusFlag::_4) &&
            mStatusFlags.isOff(StatusFlag::NeedToIncrementRefCount)) {
            arena->addSize2(mHeap ? mHeap->getSize() : 0);
            mStatusFlags.set(StatusFlag::_4);
        }
    }
    return true;
}

// NON_MATCHING: the original materialises the status constant (0xb) before the return value in both branches
bool ResourceUnit::prepareUnload() {
    bool ok;
    const auto status = mStatus.value();
    if ((status == Status::_5 || status == Status::_14 || status == Status::_15) && mResource) {
        if (auto* res = sead::DynamicCast<Resource>(mResource)) {
            mStatus = Status::_6;
            if (!res->m7()) {
                mStatus = Status::_5;
                stubbedLogFunction();
                return false;
            }
        }
        mCounter.storeNonAtomic(0);
        mEvent.resetSignal();
        ok = true;
    } else {
        ok = false;
    }
    mStatus = Status::_11;
    return ok;
}

void ResourceUnit::doRetryLoad() {
    const auto sleep_time = sead::TickSpan::makeFromMilliSeconds(30);
    for (s32 i = 0; i < 30; ++i) {
        auto* resource = sead::ResourceMgr::instance()->tryLoadWithoutDecomp(mLoadArg);
        if (auto* checked_resource = sead::DynamicCast<sead::Resource>(resource)) {
            mResource = static_cast<sead::DirectResource*>(checked_resource);
            return;
        }
        mResource = nullptr;
        if (mLoadArg.device->getLastRawError() > 0)
            stubbedLogFunction();
        sead::Thread::sleep(sleep_time);
    }
}

void ResourceUnit::requestPrepareLoad(util::TaskPostRunResult* result,
                                      const util::TaskPostRunContext& ctx) {
    if (!mHeap || mStatus != Status::_7)
        return;

    u8 lane_id;
    switch (ctx.mTask->getLaneId()) {
    case 1:
    case 2:
        lane_id = 0;
        break;
    case 3:
    case 4:
        lane_id = 1;
        break;
    case 5:
    case 6:
        lane_id = 2;
        break;
    default:
        lane_id = 0xff;
        break;
    }

    util::TaskRequest req;
    req.mHasHandle = true;
    req.mSynchronous = false;
    req.mLaneId = lane_id;
    req.mThread = ResourceMgrTask::instance()->getResourceLoadingThread();
    req.mDelegate = &ResourceMgrTask::instance()->getUnitPrepareLoadFn();
    req.mUserData = this;
    req.mName = mPath;
    if (ctx.mTask->submitRequest(req))
        result->setResult(true);
}

// NON_MATCHING: the switch over the status is a jump table in the original (ours: bit tests)
bool ResourceUnit::unloadForSync() {
    lockCacheCriticalSection();
    if (returnFalse())
        stubbedLogFunction();

    mRefCount.decrement();
    if (mStatusFlags.isOn(StatusFlag::_80000) && mRefCount == 1 &&
        ResourceMgrTask::instance()->isFlag4Set() && mStatusFlags.isOn(StatusFlag::_80000)) {
        mRefCount.decrement();
        mStatusFlags.reset(StatusFlag::_80000);
        stubbedLogFunction();
    }

    if (mRefCount == 0) {
        bool erase = true;
        if (mStatusFlags.isOn(StatusFlag::_20000)) {
            switch (mStatus.value()) {
            case Status::_9:
            case Status::_12:
            case Status::_15:
                break;
            case Status::_10:
            case Status::_13:
                mEvent.wait();
                erase = mStatus == Status::_15;
                break;
            case Status::_11:
            case Status::_14:
            default:
                erase = false;
                break;
            }
        }

        if (erase) {
            if (mCache)
                mCache->eraseUnit(this);
            else
                stubbedLogFunction();
            mStatusFlags.reset(StatusFlag::_20000);
        }
    }

    if (returnFalse())
        stubbedLogFunction();
    unlockCacheCriticalSection();
    return true;
}

void ResourceUnit::requestUnload(util::TaskPostRunResult* result,
                                 const util::TaskPostRunContext& ctx) {
    if (mRefCount > 0)
        return;

    if (returnFalse())
        stubbedLogFunction();

    {
        ControlTaskRequest req;
        req.mHasHandle = true;
        req.mSynchronous = false;
        req.mLaneId = 9;
        req.mThread = ResourceMgrTask::instance()->getResourceMemoryThread();
        req.mDelegate = &ResourceMgrTask::instance()->getUnitUnloadFn().fn;
        req.mUserData = this;
        req.mPostRunCallback = &ResourceMgrTask::instance()->getUnitUnloadFn().cb;
        req.mName = "Unload";
        mTask3.submitRequest(req);
    }
    result->setResult(false);
    if (returnFalse())
        stubbedLogFunction();
}

void ResourceUnit::requestClearCache(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& ctx) {
    if (returnFalse())
        stubbedLogFunction();

    {
        ControlTaskRequest req;
        req.mHasHandle = true;
        req.mSynchronous = false;
        req.mLaneId = 9;
        req.mThread = ResourceMgrTask::instance()->getResourceMemoryThread();
        req.mDelegate = &ResourceMgrTask::instance()->getUnitClearCacheFn().fn;
        req.mUserData = this;
        req.mPostRunCallback = &ResourceMgrTask::instance()->getUnitClearCacheFn().cb;
        req.mName = "ClearCache";
        ctx.mTask->submitRequest(req);
    }
    result->setResult(true);
    if (returnFalse())
        stubbedLogFunction();
}

// NON_MATCHING: the status == 5 test comes before the status == 1 test in the original (ours compares 1 first)
void ResourceUnit::postUnload(util::TaskPostRunResult* result,
                              const util::TaskPostRunContext& ctx) {
    if (returnFalse())
        stubbedLogFunction();

    const auto status = mStatus.value();
    if (status == Status::_5) {
        if (ctx.mCancelled) {
            result->setResult(false);
        } else {
            {
                ControlTaskRequest req;
                req.mHasHandle = true;
                req.mSynchronous = false;
                req.mLaneId = 9;
                req.mThread = ResourceMgrTask::instance()->getResourceMemoryThread();
                req.mDelegate = &ResourceMgrTask::instance()->getUnitUnloadFn().fn;
                req.mUserData = this;
                req.mPostRunCallback = &ResourceMgrTask::instance()->getUnitUnloadFn().cb;
                req.mName = "Unload";
                ctx.mTask->submitRequest(req);
            }
            result->setResult(true);
            if (returnFalse())
                stubbedLogFunction();
            return;
        }
    } else {
        if (status == Status::_1) {
            postClearCache(result, ctx);
            if (returnFalse())
                stubbedLogFunction();
            return;
        }

        if (isTask1NotQueued() || status == Status::_0 || mStatusFlags.isOff(StatusFlag::_20000)) {
            ResourceMgrTask::instance()->registerUnit(this);
            result->setResult(false);
        }
    }

    if (returnFalse())
        stubbedLogFunction();
}

void ResourceUnit::postClearCache(util::TaskPostRunResult* result,
                                  const util::TaskPostRunContext& ctx) {
    if (returnFalse())
        stubbedLogFunction();

    if (mStatus == Status::_5) {
        bool success;
        if (ctx.mCancelled) {
            if (returnFalse())
                stubbedLogFunction();
            success = false;
        } else {
            {
                ControlTaskRequest req;
                req.mHasHandle = true;
                req.mSynchronous = false;
                req.mLaneId = 9;
                req.mThread = ResourceMgrTask::instance()->getResourceMemoryThread();
                req.mDelegate = &ResourceMgrTask::instance()->getUnitClearCacheFn().fn;
                req.mUserData = this;
                req.mPostRunCallback = &ResourceMgrTask::instance()->getUnitClearCacheFn().cb;
                req.mName = "ClearCache";
                ctx.mTask->submitRequest(req);
            }
            if (returnFalse())
                stubbedLogFunction();
            success = true;
        }
        result->setResult(success);
    } else {
        ResourceUnit* unit = this;
        ResourceMgrTask::instance()->requestDeleteUnit(&unit);
        result->setResult(false);
        if (returnFalse())
            stubbedLogFunction();
    }
}

// NON_MATCHING: the MakeHeapArg is above the path buffer in the original's stack frame (ours: below), and the
// original calls prepareLoad without the null second argument that the default argument adds here
bool ResourceUnit::initLoad(void*) {
    if (returnFalse())
        stubbedLogFunction();

    mStatus = Status::_7;

    sead::FixedSafeString<384> path;
    const u32 heap_size = determineHeapSize(&path);
    if (heap_size == 0) {
        mStatusFlags.set(StatusFlag::FailedMaybe);
        if (mStatusFlags.isOn(StatusFlag::_80000)) {
            mRefCount.decrement();
            mStatusFlags.reset(StatusFlag::_80000);
            stubbedLogFunction();
        }
        mStatus = Status::_9;
        mEvent.setSignal();
        stubbedLogFunction();
        return false;
    }

    if (mStatusFlags.isOff(StatusFlag::HasHeap)) {
        ResourceMgrTask::MakeHeapArg arg;
        arg.heap_size = heap_size;
        arg.unit = this;
        arg.out_arena1 = &mArena1;
        arg.out_arena2 = &mArena2;
        arg.path = mPath;
        arg.arena = mLoadReqArena;
        auto* heap = ResourceMgrTask::instance()->makeHeapForUnit(arg);
        if (!heap) {
            mStatusFlags.set(StatusFlag::_80);
            if (mStatusFlags.isOn(StatusFlag::_80000)) {
                mRefCount.decrement();
                mStatusFlags.reset(StatusFlag::_80000);
                stubbedLogFunction();
            }
            mStatus = Status::_9;
            mEvent.setSignal();
            if (!mArena1 || !mArena1->isFlag1Set() || returnFalse())
                stubbedLogFunction();
            return false;
        }
        mLoadArg.instance_heap = heap;
        mLoadArg.load_data_heap = heap;
        mHeap = heap;
        if (returnFalse())
            stubbedLogFunction();
    } else {
        auto* heap = mHeap;
        if (heap->getMaxAllocatableSize(8) < heap_size) {
            mStatusFlags.set(StatusFlag::_80);
            if (mStatusFlags.isOn(StatusFlag::_80000)) {
                mRefCount.decrement();
                mStatusFlags.reset(StatusFlag::_80000);
                stubbedLogFunction();
            }
            mStatus = Status::_9;
            mEvent.setSignal();
            stubbedLogFunction();
            return false;
        }
        mLoadArg.instance_heap = heap;
        mLoadArg.load_data_heap = heap;
        mHeap = heap;
        if (!heap) {
            if (mStatusFlags.isOn(StatusFlag::_80000)) {
                mRefCount.decrement();
                mStatusFlags.reset(StatusFlag::_80000);
                stubbedLogFunction();
            }
            stubbedLogFunction();
            return false;
        }
        if (returnFalse())
            stubbedLogFunction();
    }

    if (mStatusFlags.isOn(StatusFlag::NeedToIncrementRefCount) && !mArenaUnitListNode2.isLinked())
        mArena2->sub_71011FD7C8(this);

    if (mStatusFlags.isOn(StatusFlag::LoadFromArchive))
        prepareLoad();

    return true;
}

u32 ResourceUnit::determineHeapSize(const sead::SafeString& path, bool flag4, bool flag1,
                                    bool flag2) {
    ResourceMgrTask::ResourceSizeInfo info;

    {
        ResourceMgrTask::GetResourceSizeInfoArg arg;
        arg.alloc_size = mAllocSize;
        arg.factory = mLoadArg.factory;
        arg.file_device = mLoadArg.device;
        arg.load_data_alignment = mLoadArg.load_data_alignment;
        arg.archive_res = mArchiveRes;
        arg.str = path;
        arg.path = mPath;
        arg.flag4_try_decomp = flag4;
        arg.flag1 = flag1;
        arg.flag2 = flag2;
        ResourceMgrTask::instance()->getResourceSizeInfo(&info, arg);
    }

    const u32 buffer_size = info.buffer_size;
    mInfoAllocSize = info.alloc_size;
    if (buffer_size != 0) {
        mLoadArg.device = info.is_archive_file_dev2 ? nullptr : info.file_device;
        return buffer_size;
    }

    auto* archive_res = mArchiveRes;
    bool exists = false;
    if (archive_res) {
        exists = archive_res->getFile(path) != nullptr;
        if (exists)
            return 0;
        stubbedLogFunction();
    } else if (info.file_device) {
        if (!info.file_device->tryIsExistFile(&exists, path) || exists)
            return 0;
        stubbedLogFunction();
    }
    return 0;
}

// NON_MATCHING: register allocation (the original computes &mLoadArg into x20 before the first branch)
void ResourceUnit::doLoad() {
    if (mFlags.isOff(Flag::_4)) {
        if (mLoadArg.device == sead::FileDeviceMgr::instance()->getMainFileDevice() ||
            mLoadArg.device == ResourceMgrTask::instance()->getOffsetReadFileDevice()) {
            mResource = sead::DynamicCast<sead::Resource>(
                sead::ResourceMgr::instance()->tryLoadWithoutDecomp(mLoadArg));
            sub_71012132C8(mPath, false);
            if (returnFalse4())
                stubbedLogFunction();
        } else {
            mResource = sead::DynamicCast<sead::Resource>(
                sead::ResourceMgr::instance()->tryLoadWithoutDecomp(mLoadArg));
        }
    } else {
        auto* decompressor = ResourceMgrTask::instance()->getSzsDecompressor();
        if (mLoadArg.device == sead::FileDeviceMgr::instance()->getMainFileDevice() ||
            mLoadArg.device == ResourceMgrTask::instance()->getOffsetReadFileDevice()) {
            mResource = sead::DynamicCast<sead::Resource>(sead::ResourceMgr::instance()->tryLoad(
                mLoadArg, sead::SafeString::cEmptyString, decompressor));
            sub_71012132C8(mPath, true);
            if (returnFalse4())
                stubbedLogFunction();
        } else {
            mResource = sead::DynamicCast<sead::Resource>(sead::ResourceMgr::instance()->tryLoad(
                mLoadArg, sead::SafeString::cEmptyString, decompressor));
        }
        ResourceMgrTask::instance()->unlockSzsDecompressorCS();
    }

    if (mResource)
        return;

    bool exists = false;
    sead::FixedSafeString<256> path_no_drive;
    sead::Path::getPathExceptDrive(&path_no_drive, mLoadArg.path);
    mLoadArg.device->tryIsExistFile(&exists, path_no_drive);
    if (!exists) {
        sead::IsDerivedFrom<sead::ArchiveFileDevice>(mLoadArg.device);
        stubbedLogFunction();
        mStatusFlags.set(StatusFlag::FailedMaybe);
        return;
    }

    u32 file_size = 0;
    if (mFlags.isOff(Flag::_4)) {
        if (!mLoadArg.device->tryGetFileSize(&file_size, mLoadArg.path))
            return;
    } else {
        if (!ResourceMgrTask::instance()->getUncompressedSize(&file_size, mLoadArg.path,
                                                              mLoadArg.device))
            return;
    }

    if (file_size == 0) {
        stubbedLogFunction();
        mStatusFlags.set(StatusFlag::FileSizeIsZero);
        return;
    }

    if (mAllocSize != 0 && mAllocSize < file_size) {
        stubbedLogFunction();
        sead::FormatFixedSafeString<256> message(
            "↓↓↓\nファイルパス               : %s\nResourceBinder::allocSize  : %u\n実際の展開後バイナリサイズ : %u\n↑↑↑\n",
            mLoadArg.path.cstr(), mAllocSize, file_size);
        mStatusFlags.set(StatusFlag::FileSizeExceedsAllocSize);
        return;
    }

    const size_t max_size = mLoadArg.load_data_heap->getMaxAllocatableSize(8);
    if (max_size < file_size) {
        stubbedLogFunction();
        sead::FormatFixedSafeString<512> message(
            "↓↓↓\nファイルパス               : %s\nMaxAllocatableSize         : %d\n実際の展開後バイナリサイズ : %u\n↑↑↑\n",
            mLoadArg.path.cstr(), max_size, file_size);
        mStatusFlags.set(StatusFlag::FileOrResInstanceTooLargeForHeap);
        return;
    }

    if (auto* factory = sead::DynamicCast<EntryFactoryBase>(mLoadArg.factory)) {
        if (mLoadArg.instance_heap->getMaxAllocatableSize(8) < factory->getResourceSize()) {
            mStatusFlags.set(StatusFlag::FileOrResInstanceTooLargeForHeap);
            return;
        }
    }

    if (mStatusFlags.isOn(StatusFlag::LoadFromArchive)) {
        stubbedLogFunction();
        return;
    }

    if (mLoadArg.device->getLastRawError() > 0) {
        stubbedLogFunction();
        doRetryLoad();
    }

    if (mResource)
        return;

    stubbedLogFunction();
    mStatusFlags.set(StatusFlag::LoadFailed);
}

}  // namespace ksys::res
