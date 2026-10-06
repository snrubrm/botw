#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgnitedThrown : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IgnitedThrown, ksys::act::ai::Action)
public:
    explicit IgnitedThrown(const InitArg& arg);
    ~IgnitedThrown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isFinished() const override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mReactionLevel_s{};
    // static_param at offset 0x28
    const float* mDamageScale_s{};
    // static_param at offset 0x30
    const float* mFinishWaterDepth_s{};
    // static_param at offset 0x38
    const bool* mIsScaling_s{};
    // static_param at offset 0x40
    const bool* mIsFinishedByOneHit_s{};
    // static_param at offset 0x48
    const bool* mIsFadeIn_s{};
    // static_param at offset 0x50
    const bool* mIsAbleGuard_s{};
    // static_param at offset 0x58
    const bool* mIsForceOnly_s{};
    // static_param at offset 0x60
    sead::SafeString mAS_s{};
    bool _70 = true;
    bool _71 = false;
    bool _72 = false;
    u8 _73[0x1];
    f32 _74 = 0.0f;
    s32 _78 = 0;
    s32 _7c = 0;
    xlink2::HandleSLink _80;
    sead::Vector3f _90 = sead::Vector3f::zero;
    u16 _9c = 0;
    bool _9e = false;
    u8 _9f[0x1];

};
KSYS_CHECK_SIZE_NX150(IgnitedThrown, 0xa0);

}  // namespace uking::action
