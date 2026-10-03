#pragma once

#include "Game/AI/AI/aiTimelineAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCTimeline : public TimelineAI {
    SEAD_RTTI_OVERRIDE(NPCTimeline, TimelineAI)
public:
    explicit NPCTimeline(const InitArg& arg);
    ~NPCTimeline() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::ai
