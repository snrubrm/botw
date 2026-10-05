#include "Game/AI/Action/actionEventCancelSleepTargetActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventCancelSleepTargetActor::EventCancelSleepTargetActor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCancelSleepTargetActor::~EventCancelSleepTargetActor() = default;

bool EventCancelSleepTargetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCancelSleepTargetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

bool EventCancelSleepTargetActor::oneShot_() {
    ksys::act::ActorConstDataAccess accessor;
    if (auto* link = ksys::evt::Manager::instance()->getBaseProcLinkFromActiveEvent(
            mActorName_d, mInstanceName_d)) {
        ksys::act::acquireActor(link, &accessor);
        if (accessor.hasProc())
            accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    }
    return true;
}

}  // namespace uking::action
