#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceArchive.h"

namespace ksys {
class OverlayArena;
}

// Complete 8A559C allocates 0x170 bytes and constructs these members; the
// singleton lifetimes and independent pack/heap methods use the same boundaries.
class DungeonPackMgr {
    SEAD_SINGLETON_DISPOSER(DungeonPackMgr)
    DungeonPackMgr() = default;
    ~DungeonPackMgr() = default;

public:
    void makeHeap();
    void cleanupAndUnregisterFactory();
    void submitLoadPackRequest(const sead::SafeString& name);
    void waitAndSetResMgrPack();
    void setResourceMgrPack();
    bool isResReady() const;
    void sub_71008A5ADC();
    bool startedLoadAndFailed() const;

private:
    ksys::res::EntryFactory<ksys::res::Archive> mFactory;
    ksys::res::Handle mHandle;
    sead::ExpHeap* mHeap = nullptr;
    ksys::OverlayArena* mArena = nullptr;
    bool mIsAocPack = false;
};
KSYS_CHECK_SIZE_NX150(DungeonPackMgr, 0x170);
