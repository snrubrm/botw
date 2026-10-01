#include "Game/AI/Action/actionEventCancelGet.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EventCancelGet::EventCancelGet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventCancelGet::~EventCancelGet() = default;

bool EventCancelGet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventCancelGet::oneShot_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    return true;
}

void EventCancelGet::loadParams_() {}

}  // namespace uking::action
