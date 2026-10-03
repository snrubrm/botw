#include "Game/AI/AI/aiEventTagRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EventTagRootAI::EventTagRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    _38 = State::_0;
    _3c = State::_0;
    _40 = 0;
}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
EventTagRootAI::~EventTagRootAI() {
    ;
}

bool EventTagRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EventTagRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    if (isRootAiParamINot5()) {
        _38 = _3c;
        _3c = State::_0;
        _40 = 0;
        _80 = mActor->checkBasicSig();
    }

    auto* actor = mActor;
    if (actor->getFieldBodyGroup()) {
        actor->m107();
        sead::Matrix34f mtx;
        actor->getHomeMtx(&mtx);
        actor->setMtx(mtx, true, true);
        actor->nullsub_4648();
    }
}

void EventTagRootAI::calc_() {
    {
        auto* actor = mActor;
        if (actor->getFieldBodyGroup()) {
            actor->m107();
            sead::Matrix34f mtx;
            actor->getHomeMtx(&mtx);
            actor->setMtx(mtx, true, true);
            actor->nullsub_4648();
        }
    }

    auto* actor = mActor;
    const bool launch =
        !actor->checkBasicSig() ? *mLaunchEventByOffSignal_m : *mLaunchEventByOnSignal_m;
    const bool changed = actor->checkBasicSig() != _80;
    if (launch) {
        if (changed) {
            _38 = _3c;
            _3c = State::_1;
            _40 = 0;
        }
    } else if (changed) {
        auto* sig_actor = mActor;
        _38 = _3c;
        _3c = State::_0;
        _40 = 0;
        if (sig_actor->checkBasicSig())
            sig_actor->emitBasicSigOn();
        else
            sig_actor->emitBasicSigOff();
    }

    sub_7100E19EDC();
    if (_3c == State::_1 || _3c == State::_2)
        actor->m107();
    _80 = mActor->checkBasicSig();
}

void EventTagRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EventTagRootAI::loadParams_() {
    getMapUnitParam(&mLaunchEventByOnSignal_m, "LaunchEventByOnSignal");
    getMapUnitParam(&mLaunchEventByOffSignal_m, "LaunchEventByOffSignal");
    getMapUnitParam(&mIsEndlessEvent_m, "IsEndlessEvent");
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

}  // namespace uking::ai
