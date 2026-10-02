#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordApproachRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordApproachRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordApproachRoot(const InitArg& arg);
    ~SiteBossSwordApproachRoot() override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mKeepDistance_s{};
    // static_param at offset 0x40
    const float* mMoveWidth_s{};
    // static_param at offset 0x48
    const float* mBaseOffsetY_s{};
    // static_param at offset 0x50
    const float* mPredictMoveFrame_s{};
    // static_param at offset 0x58
    const bool* mIsCloseMove_s{};
    // static_param at offset 0x60
    const bool* mIsPlayRunStartAS_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mOldTargetPos_d{};
    f32 _78 = 0;
    u32 _7c = 0;
    u32 _80 = 0;
    u32 _84 = 0;
    f32 _88 = 0;
    bool _8c = false;
    u8 _8d[0x9c - 0x8d];
    u32 _9c;
    u32 _a0;
    u32 _a4;
    f32 _a8;
    f32 _ac;
    u32 _b0;
    u8 _b4[0xc0 - 0xb4];
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordApproachRoot, 0xc0);

}  // namespace uking::ai
