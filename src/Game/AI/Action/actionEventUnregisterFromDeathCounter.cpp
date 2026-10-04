#include "Game/AI/Action/actionEventUnregisterFromDeathCounter.h"
#include "Game/gameEventMgr1.h"

namespace uking::action {

EventUnregisterFromDeathCounter::EventUnregisterFromDeathCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUnregisterFromDeathCounter::~EventUnregisterFromDeathCounter() = default;

bool EventUnregisterFromDeathCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventUnregisterFromDeathCounter::oneShot_() {
    EventMgr1::instance()->sub_7100E48C44(mActorName_d);
    return true;
}

void EventUnregisterFromDeathCounter::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
