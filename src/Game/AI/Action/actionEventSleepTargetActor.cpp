#include "Game/AI/Action/actionEventSleepTargetActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventSleepTargetActor::EventSleepTargetActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSleepTargetActor::~EventSleepTargetActor() = default;

bool EventSleepTargetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSleepTargetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

bool EventSleepTargetActor::oneShot_() {
    ksys::act::ActorConstDataAccess accessor;
    if (auto* link = ksys::evt::Manager::instance()->getBaseProcLinkFromActiveEvent(
            mActorName_d, mInstanceName_d)) {
        ksys::act::acquireActor(link, &accessor);
        if (accessor.hasProc())
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
    return true;
}

}  // namespace uking::action
