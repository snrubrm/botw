#pragma once

#include <xlink2/xlink2HandleELink.h>
#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSlide : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSlide, PlayerAction)
public:
    explicit PlayerSlide(const InitArg& arg);
    ~PlayerSlide() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mUpKeyInvalidTime_s{};
    // static_param at offset 0x28
    const float* mFrontSlideMaxSpeedF_s{};
    // static_param at offset 0x30
    const float* mBackSlideMaxSpeedF_s{};
    // static_param at offset 0x38
    const float* mLimitAngleDegStart_s{};
    // static_param at offset 0x40
    const float* mMaxSlipSpeed_s{};
    // static_param at offset 0x48
    const float* mSlipSpeedAdd_s{};
    // static_param at offset 0x50
    const float* mSlipSpeedDec_s{};
    // static_param at offset 0x58
    const float* mEffectContTime_s{};
    xlink2::HandleELink _60;
};
KSYS_CHECK_SIZE_NX150(PlayerSlide, 0x70);

}  // namespace uking::action
