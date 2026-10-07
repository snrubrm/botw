#include "KingSystem/Event/evtEventSystem.h"
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/gameRoot38.h"

namespace ksys::evt {

SEAD_SINGLETON_DISPOSER_IMPL(EventSystem)

// NON_MATCHING (createInstance, which has this constructor inlined): the original loads the disposer pointer's GOT slot
// before the vtable's, and stores the first three members (0x30 / 0x32 / 0x34) before the vptrs; ours schedules the
// vtable address first.
EventSystem::EventSystem() {
    for (auto& value : _130)
        value = 0;
    for (auto& flag : _3c)
        flag = true;
    _50 = 0;
}

EventSystem::~EventSystem() = default;

int EventSystem::handleMessage(const Message& message) {
    return 1;
}

// 0x71008ac100
void EventSystem::x_3(bool value) {
    uking::Root38::instance()->setFlag(5, value);
}

// 0x71008abf30
void EventSystem::sub_71008ABF30() {
    mSpeaker.sub_7100E49784();
}

// 0x71008abf38
void EventSystem::sub_71008ABF38(act::ActorConstDataAccess* accessor) {
    if (accessor)
        act::acquireActor(&mSpeaker.mLink, accessor);
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
