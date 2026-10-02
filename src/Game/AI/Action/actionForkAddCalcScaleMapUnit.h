#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAddCalcScaleMapUnit : public Fork {
    SEAD_RTTI_OVERRIDE(ForkAddCalcScaleMapUnit, Fork)
public:
    explicit ForkAddCalcScaleMapUnit(const InitArg& arg);
    ~ForkAddCalcScaleMapUnit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mStartRate_s{};
    // static_param at offset 0x38
    const float* mAddRate_s{};
    // static_param at offset 0x40
    const float* mMinAddScaleRate_s{};
    // map_unit_param at offset 0x48
    const float* mScaleTime_m{};
    f32 _50 = 0.0f;
    f32 _54 = 1.0f;
    f32 _58 = 1.0f;
};

}  // namespace uking::action
