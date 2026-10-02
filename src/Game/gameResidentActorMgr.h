#pragma once

#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking {

// Name from the CSV (ResidentActorMgr::createInstance 0x710090e0a0, init, loadByml, ...).
// Creates the actors listed in Actor/ResidentActors.byml (instance 0x71025d1be8).
class ResidentActorMgr {
    SEAD_SINGLETON_DISPOSER(ResidentActorMgr)
    ResidentActorMgr();

public:
    void init(sead::Heap* heap);
    void loadByml();
    bool resIsReady() const;
    bool parseResource();
    void generateResidentActors(sead::Heap* heap);
    void finishLoadingResidentActors();
    bool allActorsLoaded() const;
    // 0x710090eb34 (CSV __auto0): puts every resident actor to sleep.
    void sub_710090EB34();
    // 0x710090eb70 (CSV __auto2): wakes up the GameROMPlayer resident actor.
    void sub_710090EB70();
    bool hasLoadedResidentActors() const;
    ksys::act::Actor* getActorByName(const sead::SafeString& name) const;

private:
    sead::Heap* mHeap = nullptr;
    sead::FixedPtrArray<ksys::act::Actor, 40> mActors;
    sead::FixedObjArray<ksys::act::BaseProcHandle, 40> mHandles;
    // Entries with "only_res" set.
    sead::FixedObjArray<ksys::act::BaseProcHandle, 40> mOnlyResHandles;
    ksys::res::Handle mResHandle;
};
KSYS_CHECK_SIZE_NX150(ResidentActorMgr, 0x988);

}  // namespace uking
