#include "Game/gameDungeonPackMgr.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resCompactedHeap.h"
#include "KingSystem/System/OverlayArena.h"

SEAD_SINGLETON_DISPOSER_IMPL(DungeonPackMgr)

// NON_MATCHING: heap argument evaluation uses different registers and scheduling.
void DungeonPackMgr::makeHeap() {
    auto* mgr = ksys::res::ResourceMgrTask::instance();
    auto* main = mgr->mCompactedHeapMain;
    auto* mip0 = mgr->mCompactedHeapMip0;
    if (!main || !mip0) {
        mHeap = nullptr;
        return;
    }

    mHeap = sead::ExpHeap::tryCreate(main->_5c98, s64(main->_5ca0) + s64(mip0->_5ca0), "DungeonPackMgr",
                                   mgr->mCompactedHeapMainSeadHeap, true);
    if (!mHeap)
        return;

    ksys::res::registerEntryFactory(&mFactory, "pack");
    mArena = new (mHeap) ksys::OverlayArena;
    ksys::OverlayArena::InitArg arg;
    arg.size = mHeap->getMaxAllocatableSize(8);
    arg.use_best_fit_alloc_mode = false;
    arg.set_flag_1 = true;
    arg.set_flag_8 = true;
    arg.name = "DungeonPackMgr";
    arg.heap = mHeap;
    arg.heap2 = nullptr;
    arg._6 = false;
    arg.set_flag_10 = false;
    mArena->init(arg);
}

void DungeonPackMgr::submitLoadPackRequest(const sead::SafeString& name) {
    sead::FixedSafeString<128> path;
    path.format("Pack/%s.pack", name.cstr());
    ksys::res::LoadRequest request;
    request.mRequester = "DungeonPackMgr";
    request._8 = true;
    request._26 = false;
    request.mArena = mArena;
    if (ksys::aoc::Manager::instance()) {
        request.mAocFileDevice = ksys::aoc::Manager::instance()->getFileDeviceForDungeonPack(path);
        mIsAocPack = request.mAocFileDevice != nullptr;
    }
    mHandle.requestLoad(path, &request, nullptr);
}

void DungeonPackMgr::cleanupAndUnregisterFactory() {
    if (mArena) {
        delete mArena;
        mArena = nullptr;
    }
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
    ksys::res::unregisterEntryFactory(&mFactory);
}

bool DungeonPackMgr::isResReady() const {
    return mHandle.isReadyOrNeedsParse();
}

bool DungeonPackMgr::startedLoadAndFailed() const {
    return mHandle.requestedLoad();
}

void DungeonPackMgr::sub_71008A5ADC() {
    ksys::res::setResourceMgrPack(nullptr);
    if (ksys::aoc::Manager::instance())
        ksys::aoc::Manager::instance()->registerAocPack(nullptr);
    mHandle.requestUnload();
}

void DungeonPackMgr::setResourceMgrPack() {
    mHandle.parseResource(nullptr);
    if (mHandle.isSuccess()) {
        ksys::res::setResourceMgrPack(&mHandle);
        if (mIsAocPack && ksys::aoc::Manager::instance())
            ksys::aoc::Manager::instance()->registerAocPack(&mHandle);
    }
}

void DungeonPackMgr::waitAndSetResMgrPack() {
    mHandle.waitForReady();
    mHandle.parseResource(nullptr);
    if (mHandle.isSuccess()) {
        ksys::res::setResourceMgrPack(&mHandle);
        if (mIsAocPack && ksys::aoc::Manager::instance())
            ksys::aoc::Manager::instance()->registerAocPack(&mHandle);
    }
}

void DungeonPackMgr::sub_71008A5B1C() {
    ksys::res::ResourceMgrTask::instance()->waitForTaskQueuesToEmpty();
    ksys::res::ResourceMgrTask::instance()->waitForTaskQueuesToEmpty();
    ksys::res::ResourceMgrTask::instance()->waitForTaskQueuesToEmpty();
    ksys::res::ResourceMgrTask::instance()->waitForTaskQueuesToEmpty();
    ksys::res::ResourceMgrTask::instance()->waitForTaskQueuesToEmpty();
}
