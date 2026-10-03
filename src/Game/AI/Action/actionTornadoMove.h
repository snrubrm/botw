#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TornadoMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TornadoMove, ksys::act::ai::Action)
public:
    explicit TornadoMove(const InitArg& arg);
    ~TornadoMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxAmplitude_s{};
    // static_param at offset 0x28
    const float* mMinAmplitude_s{};
    // static_param at offset 0x30
    const float* mMaxSpeed_s{};
    // static_param at offset 0x38
    const float* mAmplitudeAddRate_s{};
    // static_param at offset 0x40
    const float* mDeleteTimer_s{};
    // static_param at offset 0x48
    const float* mFrequency_s{};
    // static_param at offset 0x50
    const float* mIgnoreHitFrame_s{};
    f32 _58 = 0.0f;
    u8 _5c[0x4]{};
    s32 _60 = 0;
    f32 _64 = 0.0f;
    u8 _68[0x4]{};
    s32 _6c = 0;
    f32 _70 = 0.0f;
    u8 _74[0x30];
    f32 _a4 = 0.0f;
    s32 _a8 = 0;
    s32 _ac[2]{};
    s32 _b4 = 0;
};
KSYS_CHECK_SIZE_NX150(TornadoMove, 0xb8);

}  // namespace uking::action
