#include "KingSystem/Event/evtEventSystem.h"
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace ksys::evt {

bool EventSpeaker::setSpeaker(act::Actor* actor) {
    {
        auto lock = sead::makeScopedLock(mCS);
        mLink.reset();
    }
    if (!actor)
        return true;

    bool success;
    {
        auto lock = sead::makeScopedLock(mCS);
        success = mLink.acquire(actor, false);
        if (success && mLink.hasProc()) {
            act::ActorConstDataAccess accessor;
            act::acquireActor(&mLink, &accessor);
            mPreviousPos = accessor.getPreviousPos2();
            accessor.getActorMtx().getTranslation(mPos);
        }
    }
    return success;
}

bool EventSystem::setSpeaker(act::Actor* actor) {
    if (!actor)
        return false;
    if (actor->getName() == "NPC_DRCVoice")
        return false;
    if (actor->getName() == "NPC_GodVoice")
        return false;
    if (mSpeaker.setSpeaker(actor))
        return true;
    actor->isDeletedOrDeleting();
    return false;
}

}  // namespace ksys::evt
