#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SideStepWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SideStepWait, ksys::act::ai::Action)
public:
    explicit SideStepWait(const InitArg& arg);
    ~SideStepWait() override;

    bool isChangeable() const override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x710025384c: applies a side-step jump.
    void sub_710025384C(f32 distance, f32 height);

    struct Params {
        // static_param at offset 0x20
        const float* mFirstStepDist_s{};
        // static_param at offset 0x28
        const float* mSecondStepDist_s{};
        // static_param at offset 0x30
        const float* mThirdStepDist_s{};
        // static_param at offset 0x38
        const float* mFourthStepDist_s{};
        // static_param at offset 0x40
        const float* mGravity_s{};
        // static_param at offset 0x48
        const float* mFirstStepHeight_s{};
        // static_param at offset 0x50
        const float* mSecondStepHeight_s{};
        // static_param at offset 0x58
        const float* mThirdStepHeight_s{};
        // static_param at offset 0x60
        const float* mFourthStepHeight_s{};
        // static_param at offset 0x68
        const float* mStopSpeedRatio_s{};
        // static_param at offset 0x70
        const float* mStopRotSpeedRatio_s{};
    };
    Params mParams;
    ksys::VFRValue _78{0.0f};
    u8 _84[0x24];
    u64 _a8 = 0;
    f32 _b0 = 0.0f;
    f32 _b4 = 0.0f;
    f32 _b8 = 0.0f;
    s8 _bc = -1;
    bool _bd = false;
    u8 _be[0x2];
};
KSYS_CHECK_SIZE_NX150(SideStepWait, 0xc0);

}  // namespace uking::action
