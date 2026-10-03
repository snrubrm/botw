#include "Game/AI/AI/aiNPCTimeline.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actSchedule.h"

namespace uking::ai {

NPCTimeline::NPCTimeline(const InitArg& arg) : TimelineAI(arg) {}

NPCTimeline::~NPCTimeline() = default;

bool NPCTimeline::init_(sead::Heap* heap) {
    return TimelineAI::init_(heap);
}

void NPCTimeline::enter_(ksys::act::ai::InlineParamPack* params) {
    TimelineAI::enter_(params);
}

void NPCTimeline::calc_() {
    TimelineAI::calc_();

    auto* schedule = mActor->getSchedule();
    if (schedule && schedule->_120) {
        if (!schedule->_68.isEmpty()) {
            ksys::act::ai::InlineParamPack pack;
            m36(schedule->_68, &pack);
            changeChild(schedule->_68.cstr(), &pack);
        }
        schedule->_120 = false;
    }
}

void NPCTimeline::leave_() {
    TimelineAI::leave_();
}

void NPCTimeline::loadParams_() {
    TimelineAI::loadParams_();
}

void NPCTimeline::m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params) {
    if (!name.startsWith("Wander"))
        return;

    bool is_path_rest = false;
    if (auto* child = getCurrentChild())
        is_path_rest = sead::SafeString(child->getName()) != name;

    if (auto* schedule = mActor->getSchedule())
        is_path_rest |= schedule->_12b == 0;

    if (params)
        params->addBool(is_path_rest, "IsPathRest", -1);
}

}  // namespace uking::ai
