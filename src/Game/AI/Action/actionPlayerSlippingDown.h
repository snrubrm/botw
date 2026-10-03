#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSlippingDown : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerSlippingDown, ksys::act::ai::Action)
public:
    explicit PlayerSlippingDown(const InitArg& arg);
    ~PlayerSlippingDown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mDamageInterval_s{};
    // static_param at offset 0x28
    const int* mDamageVal_s{};
    // static_param at offset 0x30
    const float* mChangeableInterval_s{};
    // static_param at offset 0x38
    const float* mChangeableIntervalInAir_s{};
    // static_param at offset 0x40
    const float* mEnableSpeedDamage_s{};
    // dynamic_param at offset 0x48
    float* mInitAddLinearImpulse_d{};
    // dynamic_param at offset 0x50
    float* mInitAddRollImpulse_d{};
    // dynamic_param at offset 0x58
    bool* mIsAddImpulse_d{};
    f32 _60 = 0.0f;
    f32 _64 = 0.0f;
    f32 _68 = 0.0f;
    f32 _6c = 0.0f;
    u32 _70 = 0;
    bool _74 = false;

};
KSYS_CHECK_SIZE_NX150(PlayerSlippingDown, 0x78);

}  // namespace uking::action
