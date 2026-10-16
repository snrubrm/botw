#include "Game/Actor/Behavior/behaviorRequestEventResident.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

RequestEventResident::RequestEventResident(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RequestEventResident::~RequestEventResident() = default;

bool RequestEventResident::init_(sead::Heap* heap) {
    return true;
}

void RequestEventResident::calc() {}

void RequestEventResident::enter() {
    auto* actor = mActor;
    _48.initWithName(actor, mEventName_s, mEntryPointName_s);
    _48.loadEvent();
    _48.sendMessageToEventMgrActor(actor);
}

void RequestEventResident::leave() {
    _48.unloadEvent();
}

void RequestEventResident::loadParams() {
    getStaticParam(&mEventName_s, "EventName");
    getStaticParam(&mEntryPointName_s, "EntryPointName");
}

}  // namespace uking::behavior
