#pragma once

#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimNoticeTurn : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(SwimNoticeTurn, WaterFloatBase)
public:
    explicit SwimNoticeTurn(const InitArg& arg);
    ~SwimNoticeTurn() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mAngSpd_s{};
    // static_param at offset 0x68
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
    u64 _80 = 0;
    f32 _88 = -1.0f;
    u8 _8c[0x4];
};
KSYS_CHECK_SIZE_NX150(SwimNoticeTurn, 0x90);

}  // namespace uking::action
