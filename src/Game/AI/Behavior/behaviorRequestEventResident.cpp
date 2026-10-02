#include "Game/AI/Behavior/behaviorRequestEventResident.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

RequestEventResident::RequestEventResident(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RequestEventResident::~RequestEventResident() = default;

bool RequestEventResident::m6(sead::Heap* heap) {
    return true;
}

void RequestEventResident::m7() {}

void RequestEventResident::m8() {
    auto* actor = mActor;
    _48.initWithName(actor, mEventName_s, mEntryPointName_s);
    _48.loadEvent();
    _48.sendMessageToEventMgrActor(actor);
}

void RequestEventResident::m9() {
    _48.unloadEvent();
}

void RequestEventResident::loadParams() {
    getStaticParam(&mEventName_s, "EventName");
    getStaticParam(&mEntryPointName_s, "EntryPointName");
}

}  // namespace uking::behavior
