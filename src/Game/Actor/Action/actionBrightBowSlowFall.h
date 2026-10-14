#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class BrightBowSlowFall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BrightBowSlowFall, ksys::act::ai::Action)
public:
    explicit BrightBowSlowFall(const InitArg& arg);
    ~BrightBowSlowFall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mGravity_s{};
    // static_param at offset 0x28
    const float* mFloatWaveCycle_s{};
    // static_param at offset 0x30
    const float* mFloatWaveWidth_s{};
    // static_param at offset 0x38
    const float* mFloatHeight_s{};
    // static_param at offset 0x40
    const float* mFloatSpring_s{};
    // static_param at offset 0x48
    const float* mFloatDamper_s{};
    // static_param at offset 0x50
    const float* mFallBrakeHeight_s{};
    // static_param at offset 0x58
    const float* mFallBrake_s{};
    // static_param at offset 0x60
    const float* mAttractionRange_s{};
    // static_param at offset 0x68
    const float* mAttractionRate_s{};
    // static_param at offset 0x70
    sead::SafeString mTailEffectKeyName_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mInitRotate_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mRotateSpeed_s{};
    Unk_71012419b4 _90;
    sead::Vector3f _b0 = sead::Vector3f::zero;
    sead::Vector3f _bc = sead::Vector3f::zero;
    bool _c8 = false;
    bool _c9 = false;
    f32 _cc = 0;
    f32 _d0 = 0;
};

}  // namespace uking::action
