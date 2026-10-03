#include "Game/gameLastBossMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking {

void LastBossMgr::sub_7100677FFC(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    if (!mActorLink.hasProc())
        mActorLink.acquire(actor, false);
}

void LastBossMgr::sub_710067807C(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    if (mActorLink.hasProc() && mActorLink.hasProcById(actor))
        mActorLink.reset();
}

}  // namespace uking
