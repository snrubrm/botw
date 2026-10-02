#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace uking::act {

Camera* Root6::sub_71009285F0() {
    if (!mCamera)
        return nullptr;
    auto* mgr = ksys::act::BaseProcMgr::instance();
    if (!mgr)
        return nullptr;
    if (!mgr->isAccessingProcSafe(mCamera, nullptr))
        return nullptr;
    return mCamera;
}

SEAD_SINGLETON_DISPOSER_IMPL(Root6)

void Root6::sub_71009287CC(ksys::act::ActorLinkConstDataAccess* accessor) {
    if (accessor)
        accessor->acquire(mCamera);
}

Camera* Root6::getCameraActor() {
    if (!mCamera)
        return nullptr;
    auto* mgr = ksys::act::BaseProcMgr::instance();
    if (!mgr)
        return nullptr;
    if (!mgr->isAccessingProcSafe(mCamera, nullptr))
        return nullptr;
    return mCamera;
}

bool Root6::sub_7100928838(Camera* camera) {
    if (mCamera)
        return false;
    mCamera = camera;
    return true;
}

void Root6::sub_7100928854(Camera* camera) {
    if (mCamera == camera)
        mCamera = nullptr;
}

}  // namespace uking::act
