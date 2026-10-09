#pragma once

#include <container/seadSafeArray.h>
#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskData.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class ActorParam;

// Native factory and pool stride prove the composition and 0xb08 extent.
class ActorPreLoadTask : public util::TaskData {
    SEAD_RTTI_OVERRIDE(ActorPreLoadTask, util::TaskData)
    friend class ActorPreLoadMgr;

public:
    // The pool factory leaves the context and padding uninitialized.
    ActorPreLoadTask() {}
    ~ActorPreLoadTask() override;

    bool sub_7100D59608();
    bool sub_7100D5947C(const sead::SafeString& name);
    bool run();

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
    sead::Vector2f _af8 = sead::Vector2f::zero;
    sead::Vector2f _b00 = sead::Vector2f::zero;
};
KSYS_CHECK_SIZE_NX150(ActorPreLoadTask, 0xb08);

// Native constructor and allocation prove the two pools and bound task delegates.
class ActorPreLoadMgr {
    SEAD_SINGLETON_DISPOSER(ActorPreLoadMgr)
    ActorPreLoadMgr();
    ~ActorPreLoadMgr();

public:
    struct Entry {
        explicit Entry(Actor* actor) : mActor(actor) {}
        void sub_7100D58B54(ActorPreLoadMgr* mgr);

        Actor* mActor;
        sead::SafeArray<sead::SafeString, 16> mNames;
        s16 mNumNames = 0;
        bool mActive = false;
        u8 _10b[5];
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x110);

    Entry* x(Actor* actor);
    void preloadActorMaybe(Entry* entry, const sead::SafeString& name);
    void sub_7100D58F28(Actor* actor);
    void update();

private:
    ActorPreLoadTask* makeTaskMaybe();
    void makeTaskMaybe(const sead::SafeString& name);
    void cleanupTasks();
    bool invoked1(void* data);
    void invoked2(util::TaskPostRunResult* result, const util::TaskPostRunContext& context);

    sead::FixedObjArray<ActorPreLoadTask, 1024> mTasks;
    sead::CriticalSection mCS;
    sead::FixedObjArray<Entry, 512> mEntries;
    util::TaskDelegateT<ActorPreLoadMgr> mTaskDelegate;
    util::TaskPostRunCallbackT<ActorPreLoadMgr> mPostRunCallback;
};
KSYS_CHECK_SIZE_NX150(ActorPreLoadMgr, 0x2e70e0);

}  // namespace ksys::act
