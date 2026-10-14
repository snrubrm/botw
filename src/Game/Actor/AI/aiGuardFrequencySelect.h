#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardFrequencySelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardFrequencySelect, ksys::act::ai::Ai)
public:
    explicit GuardFrequencySelect(const InitArg& arg);
    ~GuardFrequencySelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

    bool sub_710040CA40();

protected:
};

}  // namespace uking::ai
