#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Utils/Thread/TaskData.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class ActorParam;

// Native factory and pool stride prove the composition and 0xb08 extent.
class ActorPreLoadTask : public util::TaskData {
    SEAD_RTTI_OVERRIDE(ActorPreLoadTask, util::TaskData)

public:
    ActorPreLoadTask() = default;
    ~ActorPreLoadTask() override;

    bool sub_7100D59608();

private:
    sead::FixedSafeString<64> mName;
    res::Handle mPackHandle;
    u32 mParsedResources = 0;
    sead::SafeArray<res::ResDerived, 32> mResources{};
    u16 mNumResources = 0;
    u16 mRefCount = 0;
    u16 mState = 0;
    bool mPackRequested = false;
    bool mRunAgain = false;
    util::ManagedTaskHandle mTaskHandle;
    u8 _ae8[8];
    ActorParam* mActorParam = nullptr;
    u32 _af8 = 0;
    u32 _afc = 0;
    u32 _b00 = 0;
    u32 _b04 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorPreLoadTask, 0xb08);

// Partial interface for pointer use; instance fields and full extent are not modeled.
class ActorPreLoadMgr {
    SEAD_SINGLETON_DISPOSER(ActorPreLoadMgr)
    ActorPreLoadMgr();
    ~ActorPreLoadMgr();

public:
    struct Entry;

    Entry* x(Actor* actor);
    void preloadActorMaybe(Entry* entry, const sead::SafeString& name);
    void sub_7100D58F28(Actor* actor);
};

}  // namespace ksys::act
