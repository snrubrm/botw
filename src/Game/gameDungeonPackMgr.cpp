#include "Game/gameDungeonPackMgr.h"
#include "Game/DLC/aocManager.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/System/OverlayArena.h"

SEAD_SINGLETON_DISPOSER_IMPL(DungeonPackMgr)

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
    if (uking::aoc::Manager::instance())
        uking::aoc::Manager::instance()->registerAocPack(nullptr);
    mHandle.requestUnload();
}

void DungeonPackMgr::setResourceMgrPack() {
    mHandle.parseResource(nullptr);
    if (mHandle.isSuccess()) {
        ksys::res::setResourceMgrPack(&mHandle);
        if (mIsAocPack && uking::aoc::Manager::instance())
            uking::aoc::Manager::instance()->registerAocPack(&mHandle);
    }
}

void DungeonPackMgr::waitAndSetResMgrPack() {
    mHandle.waitForReady();
    mHandle.parseResource(nullptr);
    if (mHandle.isSuccess()) {
        ksys::res::setResourceMgrPack(&mHandle);
        if (mIsAocPack && uking::aoc::Manager::instance())
            uking::aoc::Manager::instance()->registerAocPack(&mHandle);
    }
}
