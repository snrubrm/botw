// The state update helper of EventTagRootAI (0x7100e19edc). The original has it out of line (calc_ calls
// it), which only happens when it is in a different translation unit than calc_.
#include "Game/AI/AI/aiEventTagRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::ai {

// NON_MATCHING: only the entry dispatch differs (the original tests `== 2`, then `== 0`, then the 1..2 range
// as separate compares; ours folds the zero test into the range check)
void EventTagRootAI::sub_7100E19EDC() {
    if (_3c == State::_2) {
        auto* actor = mActor;
        if (actor->checkFlag(ksys::act::Actor::ActorFlag::_3c)) {
            _38 = _3c;
            _3c = State::_3;
            _40 = 0;
            return;
        }
        actor->checkFlag(ksys::act::Actor::ActorFlag::_3d);
    }

    switch (_3c.value()) {
    case State::_1:
    case State::_2: {
        const State result = callEvent();
        if (int(result) != State::_4 && int(result) != int(State(_3c))) {
            _38 = _3c;
            _3c = result;
            _40 = 0;
            return;
        }
        break;
    }
    default:
        break;
    }
    ++_40;
}

EventTagRootAI::State EventTagRootAI::callEvent() {
    if (!sub_7100E1A170())
        return State::_3;

    auto* actor = mActor;
    actor->setFlag(ksys::act::Actor::ActorFlag::_3c, false);
    actor->setFlag(ksys::act::Actor::ActorFlag::_3d, false);

    ksys::evt::Metadata metadata;
    metadata.init(mEventFlowName_m.cstr(), mEventFlowEntryName_m.cstr(), "");
    ksys::evt::CallArg arg;
    arg.proc = actor;
    arg.metadata = &metadata;
    arg._30 = true;
    arg._31 = true;
    arg._0 = actor->getMtx();
    const bool called = ksys::evt::Manager::instance()->callEvent(arg);
    return called ? State::_2 : State::_4;
}

bool EventTagRootAI::sub_7100E1A170() {
    if (mEventFlowName_m.isEmpty())
        return false;
    if (mEventFlowName_m.isEqual("Demo021_0"))
        return false;
    if (mEventFlowName_m.isEqual("Demo008_2"))
        return false;
    return !mEventFlowName_m.isEqual("Demo008_4");
}

}  // namespace uking::ai
