#include "Game/Actor/Action/actionWaitForASTriggerEvent.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

namespace {
// The native event mapping at 0x71023c8e28 contains one 32-bit entry.
sead::SafeArray<s32, 1> sEventTypes{{72}};
}  // namespace

WaitForASTriggerEvent::WaitForASTriggerEvent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForASTriggerEvent::~WaitForASTriggerEvent() = default;

bool WaitForASTriggerEvent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForASTriggerEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitForASTriggerEvent::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForASTriggerEvent::loadParams_() {
    getDynamicParam(&mEventType_d, "EventType");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

// NON_MATCHING: the one-entry lookup is simplified and result initialization uses different stores.
void WaitForASTriggerEvent::calc_() {
    if (isFailed() || isFinished())
        return;
    auto* events = ksys::evt::Manager::instance();
    sead::FixedSafeString<128> flow;
    sead::FixedSafeString<128> entry;
    getActiveEventFlowPath_0(nullptr, &flow, &entry);
    auto* link = events->getBaseProcLinkFromActiveEvent(mActorName_d, mUniqueName_d);
    if (!link || !link->hasProc()) {
        setFailed();
        return;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(link->getProc(nullptr, nullptr));
    if (!actor)
        return;
    actor->getUniqueName();
    auto* as_list = actor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }
    ksys::as::ASList::EventQueryResults results;
    if (as_list->sub_710115FB60(&results, sEventTypes[*mEventType_d], 0, 0,
                              &ksys::as::ASList::Unk2::sub_7101163818, true)) {
        setFinished();
    }
}

}  // namespace uking::action
