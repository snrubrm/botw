#include "Game/AI/Action/actionEventUnregisterFromGetCounter.h"
#include "Game/gameEventMgr1.h"

namespace uking::action {

EventUnregisterFromGetCounter::EventUnregisterFromGetCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUnregisterFromGetCounter::~EventUnregisterFromGetCounter() = default;

bool EventUnregisterFromGetCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventUnregisterFromGetCounter::oneShot_() {
    EventMgr1::instance()->sub_7100E4908C(mActorName_d);
    return true;
}

void EventUnregisterFromGetCounter::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
