#pragma once

#include "Game/AI/AI/aiInWaterSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class FreezeInWaterSelect : public InWaterSelect {
    SEAD_RTTI_OVERRIDE(FreezeInWaterSelect, InWaterSelect)
public:
    explicit FreezeInWaterSelect(const InitArg& arg);
    ~FreezeInWaterSelect() override;
    bool isFinished() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x58
    const int* mIceBreakTime_s{};
    // aitree_variable at offset 0x60
    bool* mIsKeepFreeze_a{};
    ksys::Timer _68{0, 0};
};

}  // namespace uking::ai
