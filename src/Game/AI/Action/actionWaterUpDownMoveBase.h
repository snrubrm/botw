#pragma once

#include "Game/AI/aiUnk_7100700620.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class WaterUpDownMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterUpDownMoveBase, ksys::act::ai::Action)
public:
    explicit WaterUpDownMoveBase(const InitArg& arg);
    ~WaterUpDownMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x71002b37f8 (placeholder name): the height of the water surface below the actor (0 if none).
    f32 sub_71002B37F8();

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x30
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x38
    const float* mAccRatio_s{};
    // static_param at offset 0x40
    const float* mWaterFloatRadius_s{};
    // static_param at offset 0x48
    const float* mWaterFloatCycleTime_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    u64 _60 = 0;
    f32 _68 = 0.0f;
    f32 _6c = 0.0f;
    s32 _70 = 0;
    ksys::act::CCAccessor _74;
    Unk_7100700620 _7c;
};
KSYS_CHECK_SIZE_NX150(WaterUpDownMoveBase, 0x88);

}  // namespace uking::action
