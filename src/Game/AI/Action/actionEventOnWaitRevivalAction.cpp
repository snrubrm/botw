#include "Game/AI/Action/actionEventOnWaitRevivalAction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EventOnWaitRevivalAction::EventOnWaitRevivalAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventOnWaitRevivalAction::~EventOnWaitRevivalAction() = default;

bool EventOnWaitRevivalAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventOnWaitRevivalAction::oneShot_() {
    mActor->setRevivalFlagForUsed(true);
    return true;
}

void EventOnWaitRevivalAction::loadParams_() {}

}  // namespace uking::action
