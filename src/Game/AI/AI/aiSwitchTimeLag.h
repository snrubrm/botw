#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchTimeLag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwitchTimeLag, ksys::act::ai::Ai)
public:
    explicit SwitchTimeLag(const InitArg& arg);
    ~SwitchTimeLag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mWaitTime_m{};
    f32 _40 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(SwitchTimeLag, 0x48);

}  // namespace uking::ai
