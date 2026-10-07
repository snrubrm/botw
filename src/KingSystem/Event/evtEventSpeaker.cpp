#include "KingSystem/Event/evtEventSystem.h"
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace ksys::evt {

// 0x7100e496ac
EventSpeaker::EventSpeaker() {
    mPreviousPos.set(0, 0, 0);
    mPos.set(0, 0, 0);
}

bool EventSpeaker::getPreviousPos(sead::Vector3f* out) const {
    if (!mLink.hasProc())
        return false;
    if (out)
        *out = mPreviousPos;
    return true;
}

bool EventSpeaker::getPos(sead::Vector3f* out) const {
    if (!mLink.hasProc())
        return false;
    if (out)
        *out = mPos;
    return true;
}

bool EventSpeaker::sub_7100E497B8(act::Actor* actor) const {
    return mLink.hasProc() && mLink.hasProcById(actor);
}

// 0x7100e49784
void EventSpeaker::sub_7100E49784() {
    auto lock = sead::makeScopedLock(mCS);
    mLink.reset();
}

bool EventSpeaker::setSpeaker(act::Actor* actor) {
    sub_7100E49784();
    if (!actor)
        return true;

    bool success;
    {
        auto lock = sead::makeScopedLock(mCS);
        success = mLink.acquire(actor, false);
        if (success)
            updateActorPosition();
    }
    return success;
}

// 0x7100e496f0 (CSV evt::S3::updateActorPosition)
void EventSpeaker::updateActorPosition() {
    if (mLink.hasProc()) {
        act::ActorConstDataAccess accessor;
        act::acquireActor(&mLink, &accessor);
        mPreviousPos = accessor.getPreviousPos2();
        accessor.getActorMtx().getTranslation(mPos);
    }
}

}  // namespace ksys::evt
