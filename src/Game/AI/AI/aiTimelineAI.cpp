#include "Game/AI/AI/aiTimelineAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TimelineAI::TimelineAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool TimelineAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original keeps &mActor->getName() in a register for both discarded cstr() calls,
// and places the child name below the param pack on the stack
void TimelineAI::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getName().cstr();
    mActor->getName().cstr();
    const sead::SafeString& name = m34();
    if (!name.isEmpty() && m35(name)) {
        const sead::SafeString child = name.cstr();
        ksys::act::ai::InlineParamPack pack;
        m36(child, &pack);
        changeChild(child.cstr(), &pack);
    } else {
        const sead::SafeString child = "Idle";
        ksys::act::ai::InlineParamPack pack;
        m36(child, &pack);
        changeChild(child.cstr(), &pack);
    }
}

void TimelineAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimelineAI::loadParams_() {
    getStaticParam(&mIntervalToCheckSchedule_s, "IntervalToCheckSchedule");
}

void TimelineAI::m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params) {}

}  // namespace uking::ai
