#include "KingSystem/Effect/eftEffectModelMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Effect/eftEffect.h"

namespace ksys::eft {

bool EffectModelMgr::requestDeleteModel(act::Actor* actor, EffectModelData* data) {
    if (!data)
        return false;

    mCS.lock();
    data->decRefCnt();
    mCS.unlock();

    if (mDebugLog) {
        Effect::instance()->debugLog(
            "EffectModelMgr::requestDeleteModel() : [res:%s:%p][actor:%s:%p](ref=%d)\n",
            data->mName.cstr(), data->mRes, actor ? actor->getName().cstr() : "clusterdRenderer",
            actor, data->mRefCount);
    }
    return true;
}

bool EffectModelMgr::release(act::Actor* actor, EffectModelData* data) {
    if (!data)
        return false;

    if (mDebugLog) {
        Effect::instance()->debugLog(
            "EffectModelMgr::release() : [res:%s][actor:%s:%p](ref=%d)\n", data->mName.cstr(),
            actor ? actor->getName().cstr() : "clusterdRenderer", actor, data->mRefCount);
    }

    mCS.lock();
    data->finalize();
    mCS.unlock();
    return true;
}

}  // namespace ksys::eft
