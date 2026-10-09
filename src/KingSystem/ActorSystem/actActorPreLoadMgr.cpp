#include "KingSystem/ActorSystem/actActorPreLoadMgr.h"
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
