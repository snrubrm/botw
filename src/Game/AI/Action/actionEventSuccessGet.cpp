#include "Game/AI/Action/actionEventSuccessGet.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EventSuccessGet::EventSuccessGet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSuccessGet::~EventSuccessGet() = default;

bool EventSuccessGet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventSuccessGet::oneShot_() {
    mActor->emitDeadUpLifeZeroAndSetRevival();
    return true;
}

void EventSuccessGet::loadParams_() {}

}  // namespace uking::action
