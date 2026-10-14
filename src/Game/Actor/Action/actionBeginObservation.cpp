#include "Game/Actor/Action/actionBeginObservation.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BeginObservation::BeginObservation(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeginObservation::~BeginObservation() = default;

bool BeginObservation::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeginObservation::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mEventFlowName_m.isEmpty() || mEventFlowEntryName_m.isEmpty())
        setFailed();
}

void BeginObservation::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeginObservation::loadParams_() {
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

// NON_MATCHING: the inlined copy of EventFlowName into the FixedSafeString is laid out differently (one cstr() call
// in the original).
void BeginObservation::calc_() {
    if (isFailed())
        return;

    sead::FixedSafeString<64> flow_name;
    flow_name = mEventFlowName_m;
    if (flow_name == "SignalFlowChart")
        flow_name = "SignalFlowchart";

    ksys::evt::Metadata metadata(flow_name.cstr(), mEventFlowEntryName_m.cstr(), "EachFrame");
    ksys::evt::CallArg arg;
    arg.metadata = &metadata;
    arg.proc = mActor;
    if (auto* manager = ksys::evt::Manager::instance()) {
        if (manager->callEvent(arg)) {
            setFinished();
        } else {
            setFailed();
            manager->sub_7100DB04CC();
        }
    }
}

}  // namespace uking::action
