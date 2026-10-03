#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InTerritorySelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InTerritorySelector, ksys::act::ai::Ai)
public:
    explicit InTerritorySelector(const InitArg& arg);
    ~InTerritorySelector() override;

    bool isFailed() const override;
    bool isFinished() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710044b9f0 (placeholder name)
    bool sub_710044B9F0();

protected:
    // static_param at offset 0x38
    const float* mTerritoryArea_s{};
};

}  // namespace uking::ai
