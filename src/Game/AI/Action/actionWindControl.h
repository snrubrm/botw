#pragma once

#include "Game/AI/aiUnk_71010C3588.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WindControl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WindControl, ksys::act::ai::Action)
public:
    explicit WindControl(const InitArg& arg);
    ~WindControl() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasUpdateForPreDeleteCb() override;
    bool updateForPreDelete() override;

protected:
    void calc_() override;
    virtual f32 m32(f32 length) { return length; }

    /* 0x20 */ ksys::act::BoneHandle _20;
    // static_param at offset 0xc8
    const float* mRadius_s{};
    // static_param at offset 0xd0
    const float* mMaxSpeed_s{};
    // static_param at offset 0xd8
    const float* mMaxRadSpeed_s{};
    // static_param at offset 0xe0
    const float* mRadAccel_s{};
    // static_param at offset 0xe8
    const float* mTemperature_s{};
    // static_param at offset 0xf0
    const bool* mUseEnvTemperature_s{};
    // static_param at offset 0xf8
    const bool* mIsModelControlOnly_s{};
    // static_param at offset 0x100
    sead::SafeString mTargetNodeName_s{};
    /* 0x110 */ f32 _110 = 0;
    /* 0x118 */ Unk_710250c3c8 _118;
    /* 0x1a0 */ f32 _1a0 = 0.1f;
    /* 0x1a4 */ f32 _1a4 = 1.0f;
};

}  // namespace uking::action
