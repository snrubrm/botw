#pragma once

#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchLinkTagCheck : public SwitchAI {
    SEAD_RTTI_OVERRIDE(SwitchLinkTagCheck, SwitchAI)
public:
    explicit SwitchLinkTagCheck(const InitArg& arg);
    ~SwitchLinkTagCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34() override;
    bool m35() override;
    bool m36() override;
    bool m37() override;
    bool m38() override;

protected:
    // static_param at offset 0x38
    const int* mSignalType_s{};
    // static_param at offset 0x40
    const int* mSetEnableJobTimerTiming_s{};
};

}  // namespace uking::ai
