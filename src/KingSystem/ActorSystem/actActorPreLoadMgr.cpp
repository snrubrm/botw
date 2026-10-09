#include "KingSystem/ActorSystem/actActorPreLoadMgr.h"
#include <prim/seadScopedLock.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Event/evtEventResource.h"

namespace ksys::act {

// NON_MATCHING: instruction scheduling differs while constructing the second fixed pool.
ActorPreLoadMgr::ActorPreLoadMgr()
    : mTaskDelegate(this, &ActorPreLoadMgr::invoked1),
      mPostRunCallback(this, &ActorPreLoadMgr::invoked2) {}

// NON_MATCHING: the task constructor is outlined instead of the native resource-array constructor.
ActorPreLoadTask* ActorPreLoadMgr::makeTaskMaybe() {
    return mTasks.emplaceBack();
}

// NON_MATCHING: pool pointer addressing and register allocation differ.
ActorPreLoadMgr::Entry* ActorPreLoadMgr::x(Actor* actor) {
    sead::ThreadMgr::instance()->getCurrentThread()->getPriority();
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    return mEntries.emplaceBack(actor);
}

// NON_MATCHING: loop counter width and register allocation differ.
void ActorPreLoadMgr::preloadActorMaybe(Entry* entry, const sead::SafeString& name) {
    for (s32 i = 0; i < entry->mNumNames; ++i) {
        if (entry->mNames[i] == name)
            return;
    }
    if (entry->mNumNames >= 16 || entry->mActive)
        return;
    // Called through a pointer in the original, retaining virtual string assignment.
    (&entry->mNames[entry->mNumNames])->operator=(name);
    ++entry->mNumNames;
}

// NON_MATCHING: name loop counter width and register allocation differ.
void ActorPreLoadMgr::Entry::sub_7100D58B54(ActorPreLoadMgr* mgr) {
    if (!mActive)
        return;
    mActive = false;
    for (s32 i = 0; i < mNumNames; ++i) {
        for (auto& task : mgr->mTasks) {
            if (task.mState != 0 && mNames[i] == task.mName) {
                if (task.mRefCount)
                    --task.mRefCount;
                break;
            }
        }
    }
}

void ActorPreLoadMgr::cleanupTasks() {
    for (s32 i = 0, count = mTasks.size(); i < count; ++i) {
        auto* task = mTasks[i];
        if (!task->mTaskHandle.isTaskAttached() && task->mRefCount == 0 && task->mState == 7) {
            task->sub_7100D59608();
            mTasks.erase(i);
            --count;
            --i;
        }
    }
}

// NON_MATCHING: entry search loop counter width and branch layout differ.
void ActorPreLoadMgr::sub_7100D58F28(Actor* actor) {
    sead::ThreadMgr::instance()->getCurrentThread()->getPriority();
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto* entry = mEntries.unsafeAt(i);
        if (entry->mActor == actor) {
            entry->sub_7100D58B54(this);
            mEntries.erase(i);
            break;
        }
    }
}

// NON_MATCHING: the pool factory is inlined and its task constructor remains outlined.
void ActorPreLoadMgr::makeTaskMaybe(const sead::SafeString& name) {
    for (auto& task : mTasks) {
        if (task.mState != 0 && name == task.mName) {
            ++task.mRefCount;
            return;
        }
    }
    auto* task = makeTaskMaybe();
    if (!task || !task->sub_7100D5947C(name))
        return;
    util::LowPrioThreadMgr::Request request;
    request.lane_id = 1;
    request.flags.setDirect(6);
    request.delegate = &mTaskDelegate;
    request.user_data = task;
    request.post_callback = &mPostRunCallback;
    request.handle = &task->mTaskHandle;
    evt::submitLowPriorityRequest(request);
}

void ActorPreLoadMgr::update() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    auto* player = ActorSystem::instance()->getPlayer();
    if (player) {
        const sead::Vector2f player_pos(player->getMtx()(0, 3), player->getMtx()(2, 3));
        for (auto& entry : mEntries) {
            if (entry.mActor->getState() != BaseProc::State::Calc) {
                entry.sub_7100D58B54(this);
                continue;
            }
            const f32 dx = entry.mActor->getMtx()(0, 3) - player_pos.x;
            const f32 dz = entry.mActor->getMtx()(2, 3) - player_pos.y;
            if (!(dx * dx + dz * dz < 900.0f)) {
                entry.sub_7100D58B54(this);
            } else if (!entry.mActive) {
                entry.mActive = true;
                for (s32 i = 0; i < entry.mNumNames; ++i)
                    makeTaskMaybe(entry.mNames[i]);
            }
        }
    } else {
        for (auto& entry : mEntries)
            entry.sub_7100D58B54(this);
    }
    cleanupTasks();
}

bool ActorPreLoadMgr::invoked1(void* data) {
    auto* task = sead::DynamicCast<ActorPreLoadTask>(static_cast<util::TaskData*>(data));
    if (!task)
        return false;
    task->run();
    return true;
}

// NON_MATCHING: request stack layout and field-store scheduling differ.
void ActorPreLoadMgr::invoked2(util::TaskPostRunResult* result,
                              const util::TaskPostRunContext& context) {
    auto* task = sead::DynamicCast<ActorPreLoadTask>(
        static_cast<util::TaskData*>(context.mUserData));
    if (!task)
        return;
    const bool run_again = task->mRunAgain;
    task->mRunAgain = false;
    if (run_again && context.mUserData) {
        util::LowPrioThreadMgr::Request request;
        request.lane_id = 1;
        request.flags.setDirect(6);
        request.delegate = &mTaskDelegate;
        request.user_data = task;
        request.post_callback = &mPostRunCallback;
        // LowPrioThreadMgr initializes its task pools with ManagedTask elements.
        request.task = static_cast<util::ManagedTask*>(context.mTask);
        request.handle = &task->mTaskHandle;
        request.name = "";
        if (task->mState >= 2 && task->mState <= 4)
            request.lane_id = 2;
        evt::submitLowPriorityRequest(request);
        result->setResult(true);
    } else {
        task->mTaskHandle.finalize();
    }
}

ActorPreLoadTask::~ActorPreLoadTask() {
    if (mRefCount) {
        mRefCount = 0;
        sub_7100D59608();
    }
}

bool ActorPreLoadTask::sub_7100D59608() {
    if (mState != 0 && mState != 7)
        return false;
    if (mActorParam) {
        BaseProcMgr::instance()->requestUnloadActorParam(mActorParam);
        mActorParam = nullptr;
    }
    mPackHandle.requestUnload();
    mPackRequested = false;
    for (s32 i = 0; i < mNumResources; ++i)
        mResources[i].requestUnload();
    mName = sead::SafeString::cEmptyString;
    mNumResources = 0;
    mRefCount = 0;
    mState = 0;
    mParsedResources = 0;
    return true;
}

}  // namespace ksys::act
