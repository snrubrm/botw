#include "Game/AI/AI/aiTimelineAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actSchedule.h"

namespace uking::ai {

TimelineAI::TimelineAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool TimelineAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

const sead::SafeString& TimelineAI::m34() {
    auto* schedule = mActor->getSchedule();
    if (!schedule)
        return sead::SafeString::cEmptyString;
    return schedule->_68;
}

void TimelineAI::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::SafeString& actorName = mActor->getName();
    actorName.cstr();
    actorName.cstr();
    const sead::SafeString& name = m34();
    if (!name.isEmpty() && m35(name))
        changeChildByName(sead::SafeString(name.cstr()));
    else
        changeChildByName(sead::SafeString("Idle"));
}

void TimelineAI::calc_() {
    const sead::SafeString& name = m34();
    if (name.isEmpty())
        return;
    getCurrentChild();
    if (isCurrentChild(name) || !m35(name))
        return;

    changeChildByName(sead::SafeString(name.cstr()));

    if (!getCurrentChild() || getCurrentChild()->isFailed())
        changeChildByName(sead::SafeString("Idle"));
}

void TimelineAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimelineAI::loadParams_() {
    getStaticParam(&mIntervalToCheckSchedule_s, "IntervalToCheckSchedule");
}

void TimelineAI::m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params) {}

}  // namespace uking::ai
