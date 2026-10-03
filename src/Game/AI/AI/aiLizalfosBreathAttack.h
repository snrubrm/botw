#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LizalfosBreathAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LizalfosBreathAttack, ksys::act::ai::Ai)
public:
    explicit LizalfosBreathAttack(const InitArg& arg);
    ~LizalfosBreathAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100484734: changeChild("疲れる") with the tired time derived from the elapsed attack time.
    void sub_7100484734();

protected:
    // static_param at offset 0x38
    const int* mMinAttackTimeForTired_s{};
    // static_param at offset 0x40
    const int* mMinTiredTime_s{};
    // static_param at offset 0x48
    const float* mTiredTimeRate_s{};
    ksys::Timer _50{0, 0, 1.0f};
};

}  // namespace uking::ai
