#include "Game/AI/Action/actionEventEnableModelDraw.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EventEnableModelDraw::EventEnableModelDraw(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventEnableModelDraw::~EventEnableModelDraw() = default;

bool EventEnableModelDraw::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventEnableModelDraw::oneShot_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    return true;
}

void EventEnableModelDraw::loadParams_() {}

}  // namespace uking::action
