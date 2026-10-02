#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossSwordApproachRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordApproachRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordApproachRoot(const InitArg& arg);
    ~SiteBossSwordApproachRoot() override;
    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(sead::Vector3f* out);
    virtual bool m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual bool m39();

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
    ksys::Timer _78;  // CurrentFrame
    u32 _84 = 0;
    f32 _88 = 0;
    bool _8c = false;
    u8 _8d[0x90 - 0x8d];
    sead::Vector3f _90;  // AfterImage0Pos
    sead::Vector3f _9c;  // AfterImage1Pos
    sead::Vector3f _a8;  // MoveDstPos
    u8 _b4[0xc0 - 0xb4];
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordApproachRoot, 0xc0);

}  // namespace uking::ai
