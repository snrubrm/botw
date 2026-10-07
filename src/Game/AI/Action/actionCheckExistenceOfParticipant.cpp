#include "Game/AI/Action/actionCheckExistenceOfParticipant.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

CheckExistenceOfParticipant::CheckExistenceOfParticipant(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CheckExistenceOfParticipant::~CheckExistenceOfParticipant() = default;

bool CheckExistenceOfParticipant::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CheckExistenceOfParticipant::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CheckExistenceOfParticipant::leave_() {
    ksys::act::ai::Action::leave_();
}

void CheckExistenceOfParticipant::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

void CheckExistenceOfParticipant::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* event = ksys::evt::Manager::instance()->getActiveEvent();
    if (!event || !event->_110)
        return;
    auto* actor = event->_110->getActorByName(mActorName_d, mInstanceName_d);
    if (!actor) {
        sead::FixedSafeString<128> flow;
        sead::FixedSafeString<128> entry;
        getActiveEventFlowPath_0(mActor, &flow, &entry);
        sead::FixedSafeString<128> path;
        getActiveEventFlowPath(mActor, &path);
        setFailed();
    } else {
        if (!actor->mLink.hasProc())
            return;
        setFinished();
    }
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
