#include "KingSystem/ActorSystem/actActorPreLoadMgr.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace ksys::act {

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
