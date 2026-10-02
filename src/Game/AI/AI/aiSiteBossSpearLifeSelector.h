#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSpearLifeSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSpearLifeSelector, ksys::act::ai::Ai)
public:
    explicit SiteBossSpearLifeSelector(const InitArg& arg);
    ~SiteBossSpearLifeSelector() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const float* mPatternChangeLife2_s{};
    // static_param at offset 0x40
    const float* mPatternChangeLife3_s{};
    u32 _48 = 0;
};
KSYS_CHECK_SIZE_NX150(SiteBossSpearLifeSelector, 0x50);

}  // namespace uking::ai
