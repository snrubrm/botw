#pragma once

#include "Game/AI/Action/actionNeckSpinBeam.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniNeckSpinBeam : public NeckSpinBeam {
    SEAD_RTTI_OVERRIDE(GuardianMiniNeckSpinBeam, NeckSpinBeam)
public:
    explicit GuardianMiniNeckSpinBeam(const InitArg& arg);
    ~GuardianMiniNeckSpinBeam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;
    int m36() override { return *mMaxLengthTime_s; }

    // static_param at offset 0x178
    const int* mSpinNum_s{};
    // static_param at offset 0x180
    const int* mMaxLengthTime_s{};
    // static_param at offset 0x188
    const bool* mIsStraight_s{};
    /* 0x190 */ void* _190{};
    /* 0x198 */ u32 _198 = 0;
};

}  // namespace uking::action
