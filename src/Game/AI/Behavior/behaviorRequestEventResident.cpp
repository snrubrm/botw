#include "Game/AI/Behavior/behaviorRequestEventResident.h"

namespace uking::behavior {

RequestEventResident::RequestEventResident(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool RequestEventResident::m6(sead::Heap* heap) {
    return true;
}

void RequestEventResident::m7() {}

void RequestEventResident::m9() {
    _48.unloadEvent();
}

void RequestEventResident::loadParams() {
    getStaticParam(&mEventName_s, "EventName");
    getStaticParam(&mEntryPointName_s, "EntryPointName");
}

}  // namespace uking::behavior
