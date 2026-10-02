#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EventTagRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EventTagRootAI, ksys::act::ai::Ai)
public:
    explicit EventTagRootAI(const InitArg& arg);
    ~EventTagRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    s32 _38;
    s32 _3c;
    s32 _40;
    // map_unit_param at offset 0x48
    const bool* mLaunchEventByOnSignal_m{};
    // map_unit_param at offset 0x50
    const bool* mLaunchEventByOffSignal_m{};
    // map_unit_param at offset 0x58
    const bool* mIsEndlessEvent_m{};
    // map_unit_param at offset 0x60
    sead::SafeString mEventFlowName_m{};
    // map_unit_param at offset 0x70
    sead::SafeString mEventFlowEntryName_m{};
    bool _80 = false;
};

}  // namespace uking::ai
