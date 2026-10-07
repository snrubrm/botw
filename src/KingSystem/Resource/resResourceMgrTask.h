#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <filedevice/seadArchiveFileDevice.h>
#include <framework/seadCalculateTask.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <prim/seadStringBuilder.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadDelegateThread.h>
#include <thread/seadReadWriteLock.h>
#include <time/seadTickTime.h>
#include "KingSystem/Resource/resControlTask.h"
#include "KingSystem/Resource/resCounter.h"
#include "KingSystem/Resource/resInfoContainer.h"
#include "KingSystem/Resource/resTempResourceLoader.h"
#include "KingSystem/Resource/resUnit.h"
#include "KingSystem/Resource/resUnitPool.h"
#include "KingSystem/System/OverlayArena.h"

namespace sead {
class Heap;
class Resource;
class ParallelSZSDecompressor;
class SZSDecompressor;
}  // namespace sead

namespace ksys {
class OverlayArena;

namespace util {
class TaskMgr;
class TaskPostRunResult;
class TaskThread;
}  // namespace util
}  // namespace ksys

namespace ksys::res {

class Cache;
class BfRes;
class CompactedHeap;
class ControlTaskData;
class EntryFactoryBase;
class MemoryTaskData;
class OffsetReadFileDevice;
class TextureHandleList;
class TextureHandleMgr;

class FileDevicePrefix {
public:
    FileDevicePrefix() = default;

    void* getUserData() const { return mUserData; }
    void setUserData(void* userdata) { mUserData = userdata; }

    const sead::SafeString& getPrefix() const { return mPrefix; }
    void setPrefix(const sead::SafeString& prefix) { mPrefix = prefix; }

    bool getField28() const { return _28; }
    void setField28(bool value) { _28 = value; }

    void registerPrefix(const sead::SafeString& prefix, void* userdata, bool set28);
    void registerPrefix(const char* prefix, void* userdata, bool set28);
    void deregister();

    static constexpr size_t getListNodeOffset() { return offsetof(FileDevicePrefix, mListNode); }

private:
    sead::ListNode mListNode;
    void* mUserData = nullptr;
    sead::SafeString mPrefix;
    bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(FileDevicePrefix, 0x30);

// FIXME: very incomplete.
class ResourceMgrTask : public sead::CalculateTask, public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(ResourceMgrTask, sead::CalculateTask)
public:
    enum class LaneId {
        _0 = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        _8 = 8,
        _9 = 9,
        _10 = 10,
    };

    using ResourceUnitDelegate = sead::Delegate1RFunc<void*, bool>;
    using TaskCallback =
        sead::Delegate2Func<util::TaskPostRunResult*, const util::TaskPostRunContext&>;
    using MemoryTaskDelegate = sead::Delegate1R<ResourceMgrTask, void*, bool>;

    struct ResourceUnitDelegatePair {
        ResourceUnitDelegate fn;
        TaskCallback cb;
    };

    static ResourceMgrTask* instance() { return sInstance; }

    void prepare() override;

    void insertOverlayArena(OverlayArena* arena);

    util::TaskThread* makeResourceLoadingThread(sead::Heap* heap, bool use_game_task_thread);

    void clearAllCaches(OverlayArena* arena);
    OverlayArena* getTexHandleMgrArena() const;

    void requestDefragAllMemoryMgr();
    // 0x7101206370 (CSV defragMemory_readResDataInLargeBuf; placeholder name): the memory task behind
    // requestDefragAllMemoryMgr.
    bool defragAllMemoryMgr(void* userdata);
    bool isDefragDone() const;
    f32 getDefragProgress() const;

    void registerFactory(sead::ResourceFactory* factory, const sead::SafeString& name);
    void unregisterFactory(sead::ResourceFactory* factory);

    s32 getCacheIdx(const sead::SafeString& path) const;

    void cancelTasks();
    void waitForTaskQueuesToEmpty();
    s32 getNumActiveTasksOnResLoadingThread() const;

    OffsetReadFileDevice* getOffsetReadFileDevice() const;
    sead::ArchiveFileDevice* getArchiveFileDev1();

    void controlField9c0d88(bool off);
    void setFlag2000Or5000(s32 type);
    void resetFlag20000();

    void copyLoadRequest(ILoadRequest* request, const sead::SafeString& path,
                         const ILoadRequest& source_request);

    EntryFactoryBase* getFactoryForPath(const sead::SafeString& path) const;

    bool isFlag4Set() const;

    Handle::Status requestLoad(Handle* handle, const sead::SafeString& path,
                               const ILoadRequest& request);
    void addSExtensionPrefix(sead::StringBuilder& builder) const;
    void removeSExtensionPrefix(sead::StringBuilder& builder);
    Handle::Status requestLoadForSync(Handle* handle, const sead::SafeString& path,
                                      const ILoadRequest& request);
    void requestUnload(Handle* handle);
    void requestUnloadForSync(Handle* handle);

    void registerUnit(ResourceUnit* unit);
    void deregisterUnit(ResourceUnit* unit);

    void requestClearCache(ResourceUnit** p_unit, util::Task* task = nullptr);
    void requestClearCacheForSync(ResourceUnit** p_unit, bool clear_immediately,
                                  bool delete_immediately);

    void deleteUnit(ResourceUnit*& unit, bool sync);
    void requestDeleteUnit(ResourceUnit** p_unit);

    struct DirectLoadArg {
        LoadRequest req;
        sead::Heap* heap;
    };
    sead::DirectResource* load(const DirectLoadArg& arg);

    bool canUseSdCard() const;
    bool isHostPath(const sead::SafeString& path) const;

    bool dropSFromExtensionIfNeeded(const sead::SafeString& path,
                                    sead::BufferedSafeString& new_path, s32 dot_idx,
                                    const sead::SafeString& extension) const;

    void unloadSeadResource(sead::Resource* resource);

    u32 getResourceSize(const sead::SafeString& name, void* userdata) const;

    void registerFileDevicePrefix(FileDevicePrefix& prefix);
    void deregisterFileDevicePrefix(FileDevicePrefix& prefix);

    void callStubbedFunctionOnArenas();
    void updateResourceArenasFlag8();

    struct MakeHeapArg {
        bool _0 = false;
        u32 heap_size = 0;
        ResourceUnit* unit = nullptr;
        sead::SafeString path;
        OverlayArena* arena = nullptr;
        OverlayArena** out_arena1 = nullptr;
        OverlayArena** out_arena2 = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(MakeHeapArg, 0x38);
    sead::Heap* makeHeapForUnit(const MakeHeapArg& arg);
    // 0x710120b118 (CSV res::ResourceMgrTask::__auto4; placeholder name): destroys `*heap` through `arena` if the
    // arena's heap contains it.
    void sub_710120B118(util::DualHeap** heap, ResourceUnit* unit, OverlayArena* arena);

    struct GetUnitArg {
        const ResourceUnit::InitArg* unit_init_arg;
        OverlayArena* arena;
    };
    ResourceUnit* clearCachesAndGetUnit(const GetUnitArg& arg);

    struct SetActorCreateInitializerThreadsArg {
        sead::PtrArray<util::TaskThread>* threads;
    };
    void setActorCreateInitializerThreads(const SetActorCreateInitializerThreadsArg& arg);
    void clearActorCreateInitializerThreads();

    void pauseThreads();
    void resumeThreads();

    sead::ParallelSZSDecompressor* getSzsDecompressor();
    void unlockSzsDecompressorCS();
    bool getUncompressedSize(u32* size, const sead::SafeString& path,
                             sead::FileDevice* device) const;

    void updateCompaction();
    void setCompactionStopped(bool stopped);
    bool isCompactionStopped() const;
    void x(bool b);
    void x_0();
    void x_1(bool b);
    void auto12();
    // 0x7101206d64 (unnamed in the CSV)
    void sub_7101206D64();
    // 0x7101208400 (unnamed in the CSV): false when the KingEditor is present with _88 == 0,
    // otherwise whether flag 0x800 is set
    bool sub_7101208400() const;
    void repairAllHandlesForSync();
    bool x_2();
    // 0x710120b754 / 0x710120b864 / 0x710120b964 (placeholder names): synchronous / synchronous / asynchronous
    // "ClearAllCaches" request without an arena; x_4 also clears the texture handle cache.
    // 0x710120c5c8 (CSV res::ResourceMgrTask::isOutOfMemory): clears flag 0x1000 (true when it was set); true when
    // an arena is out of memory, or the texture handle manager is too slow (which is recorded as a panic reason).
    bool isOutOfMemory();
    void x_4();
    void x_5();
    void x_6();

    // 0x710120b6b4 (CSV res::ResourceMgrTask::x_3): adds the bfres resource to mBfResList.
    void registerBfRes(BfRes* res);

    void requestCalc();
    void waitForCalc();

    bool initTempResourceLoader(TempResourceLoader* loader, TempResourceLoader::InitArg& arg);

    bool returnTrue1();

    void clearCacheWithFileExtension(const sead::SafeString& extension);
    void clearAllCachesSynchronously(OverlayArena* arena);

    bool returnTrue();
    bool returnTrue2();

    struct ResourceSizeInfo {
        bool is_archive_file_dev2 = false;
        u32 buffer_size = 0;
        u32 alloc_size = 0;
        sead::FileDevice* file_device = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(ResourceSizeInfo, 0x18);

    struct GetResourceSizeInfoArg {
        bool flag1 = false;
        bool flag4_try_decomp = false;
        bool flag2 = false;
        u32 alloc_size;
        sead::ArchiveRes* archive_res;
        sead::FileDevice* file_device;
        sead::ResourceFactory* factory;
        u32 load_data_alignment;
        sead::SafeString str;  // TODO: rename
        sead::SafeString path;
    };
    KSYS_CHECK_SIZE_NX150(GetResourceSizeInfoArg, 0x48);

    void getResourceSizeInfo(ResourceSizeInfo* info, const GetResourceSizeInfoArg& arg);

    void removeOverlayArena(OverlayArena* arena);

    util::TaskThread* getResourceLoadingThread() const { return mResourceLoadingThread; }
    util::TaskThread* getResourceControlThread() const { return mResourceControlThread; }
    util::TaskThread* getResourceMemoryThread() const { return mResourceMemoryThread; }
    util::TaskThread* getMovableMemoryThread() const { return mMovableMemoryThread; }

    ResourceUnitDelegatePair& getUnitInitLoadFn() { return mUnitInitLoadFn; }
    auto& getUnitPrepareLoadFn() { return mUnitPrepareLoadFn; }
    auto& getUnitUnloadFn() { return mUnitUnloadFn; }
    auto& getUnitClearCacheFn() { return mUnitClearCacheFn; }
    auto& getUnitAdjustHeapFn() { return mUnitAdjustHeapFn; }

    OverlayArena* getArenaForResourceL() { return &mArenaForResourceL; }

    void setPack(Handle* pack);

private:
    enum class Flag {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _8 = 8,
        _400 = 0x400,
        _800 = 0x800,
        _1000 = 0x1000,
        _2000 = 0x2000,
        _4000 = 0x4000,
        _20000 = 0x20000,
    };

    enum class CacheControlFlag : u8 {
        ClearAllCachesRequested = 1,
    };

    friend bool isCompactionStopped();

    explicit ResourceMgrTask(const sead::TaskConstructArg& arg);
    ~ResourceMgrTask();

    // The unit delegate functions (placeholder names; 0x7101205f5c .. 0x7101206008): each forwards the
    // task user data (the ResourceUnit) to the unit's method.
    static bool sub_7101205F5C(void* unit);
    static void sub_7101205F64(util::TaskPostRunResult* result,
                               const util::TaskPostRunContext& context);
    static bool sub_7101205F7C(void* unit);
    static bool sub_7101205F84(void* unit);
    static bool sub_7101205F8C(void* unit);
    static void sub_7101205F90(util::TaskPostRunResult* result,
                               const util::TaskPostRunContext& context);
    static bool sub_7101205FA8(void* unit);
    static void sub_7101205FB0(util::TaskPostRunResult* result,
                               const util::TaskPostRunContext& context);
    static bool sub_7101205FC8(void* unit);
    static void sub_7101205FD0(util::TaskPostRunResult* result,
                               const util::TaskPostRunContext& context);
    static bool sub_7101205FE8(void* unit);
    static void sub_7101205FF0(util::TaskPostRunResult* result,
                               const util::TaskPostRunContext& context);
    static bool sub_7101206008(void* unit);

    bool calc_(void* userdata);
    // 0x7101206208 (CSV res::ResourceMgrTask::doClearCaches): the "ClearCaches" memory task: clears the caches of the
    // used arenas, then of the unused ones (stops at the first arena that cleared something).
    bool doClearCaches(void* userdata);
    // 0x71012067e0 (CSV res::ResourceMgrTask::calculateOverlayArenaHeapSizeStuff): the memory task that updates the heap
    // size of the next arena (round robin).
    bool calcOverlayArenaHeapSize(void* userdata);
    // 0x7101206040 (CSV res::ResourceMgrTask::clearAllCachesInvoker): the "ClearAllCaches" memory task: clears the
    // caches of the unused arenas (all arenas when the name of the request is empty, else the one whose heap has that
    // name).
    bool doClearAllCaches(void* userdata);
    // 0x7101206a44 (CSV res::ResourceMgrTask::m): the texture handle manager step of the calc; also latches
    // Patrol's first flag into a static (the compaction log switch).
    bool sub_7101206A44(void* userdata);
    // 0x71012068e4 (CSV res::compactionThreadFunc): the compaction thread (message 1): compacts the main and mip0
    // heaps.
    void compactionThreadFunc(sead::Thread* thread, sead::MessageQueue::Element message);
    bool doLoadOnThread(void* userdata);
    void callCacheLoad2(util::TaskPostRunResult* result, const util::TaskPostRunContext& context);
    void loadTaskRemoveCb(const util::TaskRemoveCallbackContext& context);
    void jamThreadMessageQueuesAndWait();
    void systemCalc_();
    bool callSystemCalc_(void* userdata);
    void clearUnits_();
    static void setInstance(ResourceMgrTask* task);

    static ResourceMgrTask* sInstance;

    struct InstancePtrClearer {
        ~InstancePtrClearer() {
            if (mClearOnDestruction)
                ResourceMgrTask::sInstance = nullptr;
        }

        bool mClearOnDestruction = false;
    };
    InstancePtrClearer mInstancePtrClearer;

    sead::TypedBitFlag<Flag> mFlags;
    sead::TypedBitFlag<CacheControlFlag> mCacheControlFlags;
    u32 _17c = 0;
    sead::Heap* mResSystemHeap = nullptr;
    util::TaskThread* mResourceLoadingThread = nullptr;
    util::TaskThread* mResourceControlThread = nullptr;
    util::TaskThread* mResourceMemoryThread = nullptr;
    util::TaskThread* mMovableMemoryThread = nullptr;
    sead::PtrArray<util::TaskThread>* mActorCreateInitializerThreads = nullptr;
    util::TaskMgr* mResourceControlTaskMgr = nullptr;
    util::TaskMgr* mResourceMemoryTaskMgr;
    ControlTask* mControlTask = nullptr;
    util::Task* mTask1 = nullptr;
    util::Task* mTask2 = nullptr;
    util::Task* mTask3 = nullptr;

    EntryFactoryBase* mEntryFactoryBase = nullptr;
    EntryFactoryBase* mDefaultEntryFactory = nullptr;

    sead::Buffer<Cache*> mCaches;
    sead::FixedObjArray<s32, 4> mThreadIds;
    u8* mOffsetReadBuf = nullptr;
    mutable sead::CriticalSection mSzsDecompressorCS;
    sead::CriticalSection mFactoryCS;

    ResourceUnitDelegatePair mUnitInitLoadFn;
    ResourceUnitDelegate mUnitPrepareLoadFn;
    ResourceUnitDelegate mUnitAdjustHeapFn;
    ResourceUnitDelegatePair mUnitUnloadForSyncFn;
    ResourceUnitDelegatePair mUnitUnloadFn;
    ResourceUnitDelegatePair mUnitClearCacheForSyncFn;
    ResourceUnitDelegatePair mUnitClearCacheFn;

    MemoryTaskDelegate mClearAllCachesFn;
    MemoryTaskDelegate mClearCachesFn;
    MemoryTaskDelegate mDefragAllMemoryMgrFn;

    MemoryTaskDelegate mLoadFn;
    sead::Delegate2<ResourceMgrTask, util::TaskPostRunResult*, const util::TaskPostRunContext&>
        mLoadCb;
    sead::Delegate1<ResourceMgrTask, const util::TaskRemoveCallbackContext&> mLoadTaskRemoveCb;

    MemoryTaskDelegate mCalcFn;
    MemoryTaskDelegate mCalcArenaHeapSizeFn;
    ResourceUnitDelegate mUnitDelegate17;  // TODO: rename
    ResourceUnitDelegate mUnitDeleteFn;

    s32 _4c8 = -1;
    s32 _4cc = 0;

    ResourceUnitPool mUnitPool;
    sead::CriticalSection mUnitsCS;
    sead::OffsetList<ResourceUnit> mUnits;
    sead::OffsetList<BfRes> mBfResList;

    sead::FileDevice* mSeadMainFileDevice = nullptr;
    OffsetReadFileDevice* mOffsetReadFileDevice = nullptr;
    Handle* mPackHandle = nullptr;
    sead::ArchiveFileDevice mArchiveFileDev1{nullptr};  // TODO: rename
    sead::ArchiveFileDevice mArchiveFileDev2{nullptr};  // TODO: rename
    sead::ArchiveFileDevice mArchiveFileDev3{nullptr};  // TODO: rename
    sead::CriticalSection mCritSection2;                // TODO: rename

    u32 _9c08d0 = 0;
    sead::ObjArray<sead::SafeString> mExtensions1;  // TODO: rename
    sead::ObjArray<sead::SafeString> mExtensions2;  // TODO: rename

    sead::OffsetList<OverlayArena> mArenas;
    mutable sead::CriticalSection mArenasCS;

    OverlayArena mArenaForResourceS;
    OverlayArena mArenaForResourceL;

    ResourceInfoContainer mResourceInfoContainer;

    sead::OffsetList<FileDevicePrefix> mFileDevicePrefixes;
    mutable sead::ReadWriteLock mFileDevicePrefixesLock;

    TextureHandleMgr* mTexHandleMgr = nullptr;
    TextureHandleList* mTexHandleList = nullptr;
    sead::CriticalSection mCritSection3;  // TODO: rename

    sead::Heap* mCompactedHeapMainSeadHeap = nullptr;
    u8* mCompactedHeapMainBuffer = nullptr;
    CompactedHeap* mCompactedHeapMain = nullptr;
    u8* mCompactedHeapMip0Buffer = nullptr;
    CompactedHeap* mCompactedHeapMip0 = nullptr;
    u8* mCompactedHeapMainBuffer2 = nullptr;
    sead::Atomic<u32> mCompactionCounter = 0;
    sead::Atomic<u32> _9c0d3c = 0;
    sead::Atomic<u32> _9c0d40 = 0;
    sead::AnyDelegate2<sead::Thread*, sead::MessageQueue::Element> mCompactionThreadFn;
    sead::DelegateThread* mCompactionThread = nullptr;
    Counter mCounter;

    sead::Atomic<s32> _9c0d88 = 1;
    u32 _9c0d8c = 0;
    u32 mArenaIdx = 0;
    u32 _9c0d94;
    OverlayArena::HeapSizeArg mHeapSizeArg;

    util::Task mTask;                     // TODO: rename
    sead::CriticalSection mCritSection4;  // TODO: rename
    sead::TickTime mTickTime;
    MemoryTaskDelegate mSystemCalcFn;
};
KSYS_CHECK_SIZE_NX150(sead::TaskBase, 0xd0);
KSYS_CHECK_SIZE_NX150(sead::MethodTreeNode, 0x98);
KSYS_CHECK_SIZE_NX150(ResourceMgrTask, 0x9c0eb8);

inline void FileDevicePrefix::registerPrefix(const sead::SafeString& prefix, void* userdata,
                                             bool set28) {
    setUserData(userdata);
    setPrefix(prefix);
    if (set28)
        setField28(true);
    ResourceMgrTask::instance()->registerFileDevicePrefix(*this);
}

inline void FileDevicePrefix::registerPrefix(const char* prefix, void* userdata, bool set28) {
    registerPrefix(sead::SafeString(prefix), userdata, set28);
}

inline void FileDevicePrefix::deregister() {
    if (mListNode.isLinked())
        ResourceMgrTask::instance()->deregisterFileDevicePrefix(*this);
}

}  // namespace ksys::res
