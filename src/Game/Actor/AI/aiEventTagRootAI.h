#pragma once

#include <math/seadVector.h>
#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EventTagRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EventTagRootAI, ksys::act::ai::Ai)
public:
    // Placeholder name (SEAD_ENUM round trips through the stack in sub_7100E19EDC).
    SEAD_ENUM(State, _0, _1, _2, _3, _4)

    explicit EventTagRootAI(const InitArg& arg);
    ~EventTagRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100e19edc (placeholder name)
    void sub_7100E19EDC();
    // 0x7100e1a058 (CSV AI_AI_EventTagRootAI::callEvent; declared only): calls the event flow and returns
    // State::_2 (called), _3 (demo running) or _4 (call failed).
    State callEvent();
    // 0x7100e1a170 (CSV AI_AI_EventTagRootAI::returnFalseIfDemo021_0_008_2_008_4): false for an empty flow
    // name or the demos Demo021_0 / Demo008_2 / Demo008_4.
    bool sub_7100E1A170();

protected:
    State _38;
    State _3c;
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
